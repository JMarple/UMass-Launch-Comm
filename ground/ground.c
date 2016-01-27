#include <mavlink.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>

#define MAX_IMAGES_OPEN 10

typedef struct _patchedImage
{
    int id;
    char* buf;
    char* flags;
    int numOfPacketsLeft;
} patchedImage;

void patchImageWithPacket(patchedImage* imagePtr, mavlink_file_t* imageMsg)
{
    int fileSize = imageMsg->fileSize;

    if (imagePtr->buf == 0)
    {
        imagePtr->buf = malloc(sizeof(char)*fileSize);
        imagePtr->flags = malloc(sizeof(char)*fileSize);
        imagePtr->numOfPacketsLeft = 
            fileSize / MAVLINK_MSG_FILE_FIELD_DATA_LEN + 1;
        imagePtr->id = imageMsg->id;

        int i;
        for (i = 0; i < imagePtr->numOfPacketsLeft; i++)
            imagePtr->flags[i] = 1;
    }

    int i;
    int index = imageMsg->segment*MAVLINK_MSG_FILE_FIELD_DATA_LEN;

    for (i = 0; i < imageMsg->bytes; i++)
    {
        //fwrite(&imageMsg.data[i], sizeof(char), 1, fp); 
        imagePtr->buf[index+i] = imageMsg->data[i];
    }
    
    imagePtr->flags[imageMsg->segment] = 0;
    imagePtr->numOfPacketsLeft--;

    if (imagePtr->numOfPacketsLeft <= 0)
    {
        char fileName[255];
        bzero(fileName, 255);
        sprintf(fileName, "test%d.jpg", imagePtr->id);
        FILE* file = fopen(fileName, "wb");
        int i; 
        for (i = 0; i < fileSize; i++)
        {
            fwrite(&imagePtr->buf[i], sizeof(char), 1, file); 
        }

        // Clean up image pointer so it can be resused for another time.
        fclose(file);
        free(imagePtr->buf);
        free(imagePtr->flags);
        imagePtr->buf = 0;
        imagePtr->id = -1;
        printf("Image Done!\n");
    }
    else
    {
        printf("Packets left for (id=%d) = %d\n", 
            imagePtr->id, imagePtr->numOfPacketsLeft);
    }
}

int findFirstInstanceOfId(patchedImage** images, int id)
{
    int i;
    for (i = 0; i < MAX_IMAGES_OPEN; i++)
    {
        if (images[i]->id == id)
            return i;
    }
    return -1;
}

int main()
    
{
    printf("Ground\n");

    serialInfo serial; 
     
    if (serialOpenPort(&serial, 2, 57600))
    {
        printf("Could not find com port\n"); 
        return 0;
    }

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    patchedImage* images[MAX_IMAGES_OPEN]; 

    int t;
    for (t = 0; t < MAX_IMAGES_OPEN; t++)
    {
        images[t] = malloc(sizeof(patchedImage));                
        images[t]->id = -1;
    }    

    while (1==1)
    {
        int len = serialPoll(&serial, buf, MAVLINK_MAX_PACKET_LEN);
        
        int i; 
        mavlink_message_t msg;
        mavlink_status_t status;
    
        for (i = 0; i < len; i++)
        {
            if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
            {
                printf("Got a message\n");
                switch (msg.msgid)
                {
                    // Heartbeat message
                    case MAVLINK_MSG_ID_HEARTBEAT:
                    {    
                        static int counter = 0;
                        counter++;
                        mavlink_heartbeat_t hb;
                        mavlink_msg_heartbeat_decode(&msg, &hb); 
                        printf("HEARTBEAT\n");
                        printf("Status = %d\n", hb.system_status);
                        printf("Counter = %d\n", counter);
                    }
                    break;

                    // Recieving a packet containing an image.
                    case MAVLINK_MSG_ID_FILE:
                    {
                        mavlink_file_t image;
                        mavlink_msg_file_decode(&msg, &image);
                        int index = findFirstInstanceOfId(images, image.id);

                        if (index == -1) 
                           index = findFirstInstanceOfId(images, -1); 

                        if (index == -1)
                        {
                            printf("Error: No more images!\n");
                            break;
                        }    
                        patchImageWithPacket(
                            images[index], 
                            &image);
                    }
                    break;
            
                    case MAVLINK_MSG_ID_FILE_HANDSHAKE:
                    {
                        printf("Handshake recieved\n");
                    }
                    break;
                }
            } 
        }
    } 
    
    serialClose(&serial);
}

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

void patchImageWithPacket(patchedImage* imagePtr, mavlink_image_t* imageMsg)
{
    int fileSize = imageMsg->fileSize;

    if (imagePtr->buf == 0)
    {
        imagePtr->buf = malloc(sizeof(char)*fileSize);
        imagePtr->flags = malloc(sizeof(char)*fileSize);
        imagePtr->numOfPacketsLeft = 
            fileSize / MAVLINK_MSG_IMAGE_FIELD_DATA_LEN + 1;
        imagePtr->id = imageMsg->image;

        int i;
        for (i = 0; i < imagePtr->numOfPacketsLeft; i++)
            imagePtr->flags[i] = 1;
    }

    int i;
    int index = imageMsg->segment*MAVLINK_MSG_IMAGE_FIELD_DATA_LEN;

    printf("Num of bytes = %d\n", imageMsg->bytes);

    for (i = 0; i < imageMsg->bytes; i++)
    {
        //fwrite(&imageMsg.data[i], sizeof(char), 1, fp); 
        imagePtr->buf[index+i] = imageMsg->data[i];
    }
    
    imagePtr->flags[imageMsg->segment] = 0;
    imagePtr->numOfPacketsLeft--;

    if (imagePtr->numOfPacketsLeft <= 0)
    {
        printf("Imagesize = %d\n", fileSize);
        char fileName[255];
        bzero(fileName, 255);
        sprintf(fileName, "test%d.jpg", imagePtr->id);
        printf("File = %s", fileName);
        FILE* file = fopen(fileName, "wb");
        int i; 
        for (i = 0; i < fileSize; i++)
        {
            fwrite(&imagePtr->buf[i], sizeof(char), 1, file); 
        }
        fclose(file);
        free(imagePtr->buf);
        imagePtr->buf = 0;
        imagePtr->id = -1;
        free(imagePtr->flags);
        printf("Image Done!\n");
    }
    else
    {
        printf("Not yet = %d\n", imagePtr->numOfPacketsLeft);
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
     
    if (serialOpenPort(&serial, 1, 9600))
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
                printf("Data Receieved!\n");
                switch (msg.msgid)
                {
                    // Heartbeat message
                    case MAVLINK_MSG_ID_HEARTBEAT:
                    {    
                        mavlink_heartbeat_t hb;
                        mavlink_msg_heartbeat_decode(&msg, &hb); 
                        printf("HEARTBEAT\n");
                        printf("Status = %d\n", hb.system_status);
                    }
                    break;

                    // Recieving a packet containing an image.
                    case MAVLINK_MSG_ID_IMAGE:
                    {
                        mavlink_image_t image;
                        mavlink_msg_image_decode(&msg, &image);
                        int index = findFirstInstanceOfId(images, image.image);

                        if (index == -1) 
                           index = findFirstInstanceOfId(images, -1); 

                        if (index == -1)
                        {
                            printf("Error: No more images!\n");
                            break;
                        }    
                        printf("Index = %d\n", index); 
                        patchImageWithPacket(
                            images[index], 
                            &image);
                    }
                    break;
                }
            } 
        }
        
    } 
    
    serialClose(&serial);
}

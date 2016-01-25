#include <mavlink.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>

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

    char* currentImage = 0;
    int currentImageNumLeft = 0;

    FILE* fp;
    fp = fopen("test.jpg", "wb");

    int PACKET_SIZE = MAVLINK_MSG_IMAGE_FIELD_DATA_LEN;

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
                    case MAVLINK_MSG_ID_HEARTBEAT:
                    {    
                        mavlink_heartbeat_t hb;
                        mavlink_msg_heartbeat_decode(&msg, &hb); 
                        printf("HEARTBEAT\n");
                        printf("Status = %d\n", hb.system_status);
                    }
                    break;

                    case MAVLINK_MSG_ID_IMAGE:
                    {
                        mavlink_image_t image;
                        mavlink_msg_image_decode(&msg, &image);
                        printf("IMAGE\n");
                        printf("Segment = %d\n", image.segment);

                        int fileSize = image.numSegments*PACKET_SIZE;

                        if (currentImage == 0)
                        {
                            currentImage = malloc(sizeof(char)*fileSize);
                            currentImageNumLeft = image.numSegments;
                        }

                        int i;

                        // TODO: image.bytes is misnamed, its actually 
                        // image.numOfSegmentsInImage or somethinng of that nature.
                        int index = image.segment*PACKET_SIZE;

                        for (i = 0; i < image.bytes; i++)
                        {
                            fwrite(&image.data[i], sizeof(char), 1, fp); 
                            currentImage[index+i] = image.data[i]; 
                        }
 
                        currentImageNumLeft--;
                        
                        if (currentImageNumLeft <= 0)
                        {
                            fclose(fp);
                            printf("Image Done!\n");
                        }
                        else
                            printf("Not yet = %d\n", currentImageNumLeft);
                     }
                    break;
                }
            } 
        }
        
    } 
    
    serialClose(&serial);
}

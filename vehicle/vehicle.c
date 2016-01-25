#include <mavlink.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <unistd.h>
#define ROCKET_ID 13

// Sends a general heartbeat message to the serial port
void sendGeneralHeartbeat(serialInfo* info, uint8_t status)
{
    mavlink_message_t msg;

    mavlink_msg_heartbeat_pack(ROCKET_ID, MAV_GENERAL_SYSTEM, &msg, status);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN]; 
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); 

    serialSend(info, buf, len);
}

char* sendImage(serialInfo* info, FILE* fp)
{
    int c;
    int lc = 0;
    int segment = 0;

    // Determine size of file by going to the back of the file
    // and figuring out the position.  Then return back to the 
    // front of the file;
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
 
    // Allocate enough memory to store the entire file in memory.
    // This is so if we need to, we can resend certain packets. 
    char* fileContents = malloc(sizeof(char)*sz);

    int PACKET_SIZE = MAVLINK_MSG_IMAGE_FIELD_DATA_LEN;
    char segbuf[MAVLINK_MSG_IMAGE_FIELD_DATA_LEN];
 
    // Integer division to get number of segments needed to send
    // this file. 
    int maxSegments = sz / PACKET_SIZE + 1;

    printf("Loading file...\n");

    // Move the file from the disk to ram
    while (1==1)
    { 
        // Get the next character from the file.
        c = fgetc(fp); 
        if (feof(fp)) break; 

        fileContents[lc++] = c;        
    }

    printf("File Loaded\n");
    lc = 0;
    while (lc < sz)
    {
        // Save characters to buffer.
        segbuf[lc%PACKET_SIZE] = fileContents[lc++];        

        if ( (lc%PACKET_SIZE == 0 && lc != 0) || (lc >= sz) ) 
        {
            mavlink_image_t imgmsg;
            imgmsg.segment = segment;
            imgmsg.image = 0; 
            imgmsg.numSegments = maxSegments;
            imgmsg.bytes = (lc >= sz) ? sz % PACKET_SIZE : PACKET_SIZE;

            int i;
            for (i = 0; i < PACKET_SIZE; i++)
            {
                imgmsg.data[i] = segbuf[i];
            }

            mavlink_message_t msg;

            mavlink_msg_image_pack(ROCKET_ID, MAV_GENERAL_SYSTEM, &msg, 
                imgmsg.segment, imgmsg.image, imgmsg.numSegments, 
                imgmsg.bytes, imgmsg.data);

            uint8_t buf[MAVLINK_MAX_PACKET_LEN]; 
            uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); 

            serialSend(info, buf, len);
        
            printf("Sent Segment %d\n", segment);
            segment++; 
            usleep(100);
        }
    }

    return fileContents;
}

int main() 
{
    printf("Vehicle\n"); 

    serialInfo serial;
    if (serialOpenPort(&serial, 0, 9600))
    {
        printf("Could not find com Port\n");
        return 0;
    }   

    sendGeneralHeartbeat(&serial, MAV_STATUS_OK); 
    sendImage(&serial, fopen("vehicle/testimage2.jpg", "r")); 
    serialClose(&serial); 
}

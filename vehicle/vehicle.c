#include <mavlink.h>
#include <stdio.h>
#include "serial.h"

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

void sendImage(serialInfo* info, FILE* fp)
{
    int c;
    int lc = 0;
    int segment = 0;
    char segbuf[48];

    // Determine size of file by going to the back of the file
    // and figuring out the position.  Then return back to the 
    // front of the file;
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
   
    // Integer division to get number of segments needed to send
    // this file. 
    int maxSegments = sz / 48 + 1;

    while (1==1)
    { 
        // Get the next character from the file.
        c = fgetc(fp); 
        if (feof(fp)) break; 

        // Save characters to buffer.
        segbuf[lc++] = c;        
        if (lc >= 48) 
        {
            mavlink_image_t imgmsg;
            imgmsg.segment = segment;
            imgmsg.image = 0; 
            imgmsg.bytes = maxSegments;

            int i;
            for (i = 0; i < 45; i++)
                imgmsg.data[i] = segbuf[i];

            mavlink_message_t msg;

            mavlink_msg_image_pack(ROCKET_ID, MAV_GENERAL_SYSTEM, &msg, 
                imgmsg.segment, imgmsg.image, imgmsg.bytes, imgmsg.data);

            uint8_t buf[MAVLINK_MAX_PACKET_LEN]; 
            uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); 

            serialSend(info, buf, len);
        
            lc = 0;  
            printf("Sent Segment %d\n", segment);
            segment++; 
        }
    }
}

int main() 
{
    printf("Vehicle\n"); 

    serialInfo serial;
    if (serialOpenPort(&serial, 16, 9600))
    {
        printf("Could not find com Port\n");
        return 0;
    }   
 
    sendGeneralHeartbeat(&serial, MAV_STATUS_OK); 
    sendImage(&serial, fopen("vehicle/testimage.jpg", "r")); 
    serialClose(&serial); 
}

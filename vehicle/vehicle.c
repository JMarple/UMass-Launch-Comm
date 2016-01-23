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
    
    serialClose(&serial); 
}

#include <mavlink.h>
#include <stdio.h>
#include "rs232.h"

#define ROCKET_ID 13

typedef struct 
{
    int comPort;
    int baud;
    char mode[4];
} serialInfo;

int serialOpenPort(serialInfo* info, int comPort, int baud)
{
    info->comPort = comPort;   
    info->baud = baud;
    info->mode[0] = '8';
    info->mode[1] = 'N';
    info->mode[2] = '1';
    info->mode[3] = 0; 
    return RS232_OpenComport(info->comPort, info->baud, info->mode);
}

void serialClose(serialInfo* info)
{
    RS232_CloseComport(info->comPort);
}

void serialSend(serialInfo* info, unsigned char* buf, int len)
{
    RS232_SendBuf(info->comPort, buf, len); 
}

// Sends a general heartbeat message to the serial port
void sendGeneralHeartbeat(uint8_t status)
{
    mavlink_message_t msg;

    mavlink_msg_heartbeat_pack(ROCKET_ID, MAV_GENERAL_SYSTEM, &msg, status);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN]; 
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); 
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
 
    sendGeneralHeartbeat(MAV_STATUS_OK); 
    
    serialClose(&serial); 
}

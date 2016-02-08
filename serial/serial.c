#include "serial.h"
#include "rs232.h"

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
    double numBytesPerSecond = (info->baud / 8);
    int uSecondsForTransmission = 1000000*len / numBytesPerSecond; 

    // Ensure enough time is given for the serial data to be sent.
    usleep(uSecondsForTransmission);  
}

int serialPoll(serialInfo* info, unsigned char* buf, int bufSize)
{
    return RS232_PollComport(info->comPort, buf, bufSize); 
}

int pollSerialForMessage(
    serialInfo* info, 
    mavlink_message_t* msg)
{
    static int i = 0;
    static int len = 0;
    static uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    mavlink_status_t status;

    while (1==1)
    {
        for (; i < len; i++)
        {
            if (mavlink_parse_char(
                MAVLINK_COMM_0, 
                buf[i], 
                msg, 
                &status))
            {
                i++;
                return 1;
            }           
        } 

        len = serialPoll(info, buf, MAVLINK_MAX_PACKET_LEN);
        i = 0; 
        if (len <= 0) break;          
    } 

    return 0;
}



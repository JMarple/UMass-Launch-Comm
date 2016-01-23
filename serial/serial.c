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
}

int serialPoll(serialInfo* info, unsigned char* buf, int bufSize)
{
    return RS232_PollComport(info->comPort, buf, bufSize); 
}

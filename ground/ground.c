#include <mavlink.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <unistd.h>
#define MAX_FILES_OPEN 10

typedef struct _patchedFile
{
    int id;
    char* buf;
    char* flags;
    int numOfPacketsLeft;
    int fileSize;
    int finishRequest;
} patchedFile;

void saveCompleteFile(patchedFile* filePtr)
{
    char fileName[255];
    bzero(fileName, 255);
    sprintf(fileName, "test%d.jpg", filePtr->id);
    FILE* file = fopen(fileName, "wb");

    int i;
    for (i = 0; i < filePtr->fileSize; i++)
    {
        fwrite(&filePtr->buf[i], sizeof(char), 1, file); 
    }

    // Clean up image pointer so it can be resused for another time.
    fclose(file);
    free(filePtr->buf);
    free(filePtr->flags);
    filePtr->buf = 0;
    filePtr->id = -1;
    filePtr->finishRequest = 0;
    printf("Image Done!\n");
}

int getNumberOfPacketsMissing(patchedFile* filePtr)
{
    int i, left = 0;

    for (i = 0; i < filePtr->fileSize / MAVLINK_MSG_FILE_FIELD_DATA_LEN + 1; i++)
    {
       if (filePtr->flags[i] == 1) left++; 
    }

    return left;
}

void patchFileWithPacket(patchedFile* filePtr, mavlink_file_t* fileMsg)
{
    int fileSize = fileMsg->fileSize;

    if (filePtr->buf == 0)
    {
        filePtr->buf = malloc(sizeof(char)*fileSize);
        filePtr->flags = malloc(sizeof(char)*fileSize);

        filePtr->numOfPacketsLeft = 
            fileSize / MAVLINK_MSG_FILE_FIELD_DATA_LEN + 1;
        filePtr->id = fileMsg->id;

        int i;
        for (i = 0; i < filePtr->numOfPacketsLeft; i++)
            filePtr->flags[i] = 1;
        
        filePtr->fileSize = fileSize;
    }

    int i;
    int index = fileMsg->segment*MAVLINK_MSG_FILE_FIELD_DATA_LEN;

    for (i = 0; i < fileMsg->bytes; i++)
    {
        filePtr->buf[index+i] = fileMsg->data[i];
    }
    filePtr->flags[fileMsg->segment] = 0;
    filePtr->numOfPacketsLeft--;
    int left = getNumberOfPacketsMissing(filePtr);
    printf("Got packet %d, left (id=%d) = %d\n", fileMsg->segment, filePtr->id, left);
}

int findFirstInstanceOfId(patchedFile** files, int id)
{
    int i;
    for (i = 0; i < MAX_FILES_OPEN; i++)
    {
        if (files[i]->id == id)
            return i;
    }
    return -1;
}

void requestPacket(serialInfo* info, int id, int packetNum)
{
    mavlink_message_t msg; 
        
    mavlink_msg_file_request_packet_pack(13, MAV_GENERAL_SYSTEM, &msg, id, packetNum);
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

    serialSend(info, buf, len);
}

void sendFileConfirmed(serialInfo* info, int id)
{
    mavlink_message_t msg; 
        
    mavlink_msg_file_confirm_pack(13, MAV_GENERAL_SYSTEM, &msg, id);
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

    serialSend(info, buf, len);
}

void sendHandshakeMessage(serialInfo* info)
{
    mavlink_message_t msg;    
        
    mavlink_msg_handshake_pack(13, MAV_GENERAL_SYSTEM, &msg, 0);
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    
    serialSend(info, buf, len); 
}

void waitForVehicleCOM(serialInfo* info)
{
    while (1==1)
    {
        mavlink_message_t msg;
        if (pollSerialForMessage(info, &msg))
        {
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT)
                break; 
        }

        // Wait for half second
        usleep(500000);
        printf("..still Waiting\n");
        sendHandshakeMessage(info);
    }

    printf("Found Vehicle!\n");
}

int main()
{
    serialInfo serial; 
     
    if (serialOpenPort(&serial, 2, 57600))
    {
        printf("Could not find com port\n"); 
        return 0;
    }

    printf(".............................\n");
    printf("UMass COM-Link Ground Station\n");
    printf("Waiting for vehicle COM...\n");

    waitForVehicleCOM(&serial);

    patchedFile* files[MAX_FILES_OPEN]; 

    int t;
    for (t = 0; t < MAX_FILES_OPEN; t++)
    {
        files[t] = malloc(sizeof(patchedFile));                
        files[t]->id = -1;
        files[t]->finishRequest = 0;
        files[t]->buf = 0;
    }    

    while (1==1)
    {
        mavlink_message_t msg;
        if (pollSerialForMessage(&serial, &msg))
        {
            switch (msg.msgid)
            {
                // Heartbeat message
                case MAVLINK_MSG_ID_HEARTBEAT:
                {    
                    static int counter = 0;
                    counter++;
                    mavlink_heartbeat_t hb;
                    mavlink_msg_heartbeat_decode(&msg, &hb); 
                    printf("Heartbeat! %d\n", counter);
                }
                break;

                // Recieving a packet containing a file.
                case MAVLINK_MSG_ID_FILE:
                {
                    static int counter = 0;
                    counter++;

                    mavlink_file_t file;
                    mavlink_msg_file_decode(&msg, &file);
                    int index = findFirstInstanceOfId(files, file.id);

                    // If the id supplied by the message doesn't
                    // exist, that means this is a new file.  Find
                    // an index that is not used if the file is new.
                    if (index == -1) 
                       index = findFirstInstanceOfId(files, -1); 

                    // If there are no more space to save data, 
                    // report the error.
                    if (index == -1)
                    {
                        printf("Error: No more space!\n");
                        break;
                    }    
                    patchFileWithPacket(
                        files[index], 
                        &file);
                }
                break;
        
                // The vehicle says we recieved all the data
                // Check for any missing data.  If there is missing
                // data, request it, otherwise respond saying all
                // the data is good. 
                case MAVLINK_MSG_ID_FILE_CONFIRM:
                {
                    mavlink_file_confirm_t confirm;                   
                    mavlink_msg_file_confirm_decode(&msg, &confirm);
                   
                    int index = findFirstInstanceOfId(files, confirm.id);
                    // There is no item that exists to confirm..? 
                    if (index == -1)
                    {
                        printf("Vehicle requested confirmation of id that we don't have\n");
                        sendFileConfirmed(&serial, confirm.id);
                        break;
                    } 

                    int q, flag= 0;
                    for (q = 0; q < files[index]->fileSize / MAVLINK_MSG_FILE_FIELD_DATA_LEN + 1; q++)
                    {
                        if (files[index]->flags[q] != 0)
                        {
                            flag = 1;      
                            break;
                        }
                    }      
                    
                    if (flag == 0)
                    {
                        saveCompleteFile(files[index]);
                        sendFileConfirmed(&serial, files[index]->id);
                    }
                    else
                    {
                        if (files[index]->finishRequest == 0)
                        {
                            int left = getNumberOfPacketsMissing(files[index]);
                            printf("NUMBER OF DROPPED PACKETS = %d\n", left);
                            files[index]->finishRequest = 1;
                        }
                        printf("Requesting Packet %d\n", q);
                        requestPacket(&serial, files[index]->id, q); 
                    }
                }
                break;
            }
        }
    } 
    
    serialClose(&serial);
}

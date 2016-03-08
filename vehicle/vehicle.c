#include <mavlink.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>

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

void sendFileConfirm(serialInfo* info, int id)
{
    mavlink_message_t msg;
    mavlink_msg_file_confirm_pack(ROCKET_ID, MAV_GENERAL_SYSTEM, &msg, id);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN]; 
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); 

    serialSend(info, buf, len);
}

void sendFilePacket(
    serialInfo* info, 
    char* fileContents, 
    int packetNum, 
    int fileSize,
    int imageId)
{
    int PACKET_SIZE = MAVLINK_MSG_FILE_FIELD_DATA_LEN;
    char segbuf[MAVLINK_MSG_FILE_FIELD_DATA_LEN];
   
    int lc = packetNum*PACKET_SIZE; 

    while (lc < fileSize) 
    {
        segbuf[lc%PACKET_SIZE] = fileContents[lc];        
        lc++;

        if ( (lc%PACKET_SIZE == 0 && lc != 0) || (lc >= fileSize) ) 
        {
            mavlink_file_t imgmsg;
            imgmsg.segment = packetNum;
            imgmsg.id = imageId; 
            imgmsg.fileSize = fileSize;
            imgmsg.bytes = (lc >= fileSize) ? fileSize % PACKET_SIZE : PACKET_SIZE;

            int i;
            for (i = 0; i < PACKET_SIZE; i++)
            {
                imgmsg.data[i] = segbuf[i];
            }

            mavlink_message_t msg;

            mavlink_msg_file_pack(ROCKET_ID, MAV_GENERAL_SYSTEM, &msg, 
                imgmsg.segment, imgmsg.id, imgmsg.fileSize, 
                imgmsg.bytes, imgmsg.data);

            uint8_t buf[MAVLINK_MAX_PACKET_LEN]; 
            uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); 

            serialSend(info, buf, len);
        
            printf("Sent Segment %d\n", packetNum);
            break;
        }
    }
} 

int getFileSize(FILE* fp)
{
    // Determine size of file by going to the back of the file
    // and figuring out the position.  Then return back to the 
    // front of the file;
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

char* getFile(FILE* fp)
{
    char c;
    int lc = 0;
    int sz = getFileSize(fp);

    // Allocate enough memory to store the entire file in memory.
    // This is so if we need to, we can resend certain packets. 
    char* fileContents = malloc(sizeof(char)*sz);

    // Move the file from the disk to ram
    while (1==1)
    { 
        // Get the next character from the file.
        c = fgetc(fp); 
        if (feof(fp)) break; 

        fileContents[lc++] = c;        
    }

    return fileContents;
}

int getNumberOfPackets(int fileSize)
{
    int PACKET_SIZE = MAVLINK_MSG_FILE_FIELD_DATA_LEN;

    // Integer division to get number of segments needed to send
    // this file. 
    return fileSize / PACKET_SIZE + 1;
}

char* blockingSendFile(serialInfo* info, FILE* fp)
{
    static int id = 0; id++;
    //uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    // Get information about the file.
    int sz = getFileSize(fp);
    int maxPackets = getNumberOfPackets(sz);
    char* fileContents = getFile(fp);
    
    int packetNum = 0;
    while (packetNum < maxPackets)
    {
        sendFilePacket(info, fileContents, packetNum, sz, id);
        packetNum++;
    }

    /* Get response from ground station */
    while (1==1)
    {
        sendFileConfirm(info, id);
        usleep(200000);

        mavlink_message_t msg;
        while (pollSerialForMessage(info, &msg))
        {
            if (msg.msgid == MAVLINK_MSG_ID_FILE_CONFIRM)
            {
                printf("Done!\n");
                return fileContents; 
            }
            else if (msg.msgid == MAVLINK_MSG_ID_FILE_REQUEST_PACKET)
            {
                mavlink_file_request_packet_t packet;
                mavlink_msg_file_request_packet_decode(&msg, &packet);

		printf("Got message file request for: %d\n", packet.segment);
                sendFilePacket(info, fileContents, packet.segment, sz, id); 
            }
        }
    }

    return fileContents;
} 

int main() 
{
    printf("Vehicle\n"); 

    int pid;
    pid = fork();

    if (pid == 0) // Child
    {
	chdir("./python");
        execl("/bin/sh", "sh", "run.sh", (char*)NULL);
        return 0;    
    }  
    
    serialInfo serial;
    if (serialOpenPort(&serial, 2, 57600))
    {
        printf("Could not find com Port\n");
        return 0;
    }   

    int counter = 0;

    while (1==1)
    {
        sendGeneralHeartbeat(&serial, MAV_STATUS_OK); 
        usleep(500000);
        counter++;

        if( access( "files.lock", F_OK ) == -1 )
        {
            DIR *d;
            struct dirent *dir;
            d = opendir("./python/launchData");
	    if (d)
            {
		while ((dir = readdir(d)) != NULL)
                {
        	    	if (dir->d_name[0] != '.')
        	    	{
        	    	     char fileName[255];
        	    	     sprintf(fileName, "./python/launchData/%s", dir->d_name);

        	    		 printf("%s\n", fileName);

                         char* firstFile =
                             blockingSendFile(&serial,
                             fopen(fileName, "r"));
                         free(firstFile);
        	    	}
        	    }

        	    closedir(d);
            }

            break;
        }
    }

    serialClose(&serial); 

    return 0;
}

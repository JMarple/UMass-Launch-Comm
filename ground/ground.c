#include <mavlink.h>
#include <stdio.h>
#include "serial.h"

int main()
{
    printf("Ground\n");

    serialInfo serial; 
     
    if (serialOpenPort(&serial, 16, 9600))
    {
        printf("Could not find com port\n"); 
        return 0;
    }

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

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
                }
            } 
        }
        
    } 
    
    serialClose(&serial);
}

/** @file
 *	@brief MAVLink comm protocol testsuite generated from UMassLaunchComm.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef UMASSLAUNCHCOMM_TESTSUITE_H
#define UMASSLAUNCHCOMM_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_UMassLaunchComm(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

	mavlink_test_UMassLaunchComm(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_heartbeat(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_heartbeat_t packet_in = {
		5
    };
	mavlink_heartbeat_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.system_status = packet_in.system_status;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_pack(system_id, component_id, &msg , packet1.system_status );
	mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.system_status );
	mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_send(MAVLINK_COMM_1 , packet1.system_status );
	mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_file(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_file_t packet_in = {
		963497464,17443,17547,17651,"KLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXY"
    };
	mavlink_file_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.fileSize = packet_in.fileSize;
        	packet1.segment = packet_in.segment;
        	packet1.id = packet_in.id;
        	packet1.bytes = packet_in.bytes;
        
        	mav_array_memcpy(packet1.data, packet_in.data, sizeof(char)*42);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_file_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_pack(system_id, component_id, &msg , packet1.segment , packet1.id , packet1.fileSize , packet1.bytes , packet1.data );
	mavlink_msg_file_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.segment , packet1.id , packet1.fileSize , packet1.bytes , packet1.data );
	mavlink_msg_file_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_file_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_send(MAVLINK_COMM_1 , packet1.segment , packet1.id , packet1.fileSize , packet1.bytes , packet1.data );
	mavlink_msg_file_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_file_handshake(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_file_handshake_t packet_in = {
		17235
    };
	mavlink_file_handshake_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.id = packet_in.id;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_handshake_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_file_handshake_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_handshake_pack(system_id, component_id, &msg , packet1.id );
	mavlink_msg_file_handshake_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_handshake_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id );
	mavlink_msg_file_handshake_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_file_handshake_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_file_handshake_send(MAVLINK_COMM_1 , packet1.id );
	mavlink_msg_file_handshake_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_UMassLaunchComm(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_heartbeat(system_id, component_id, last_msg);
	mavlink_test_file(system_id, component_id, last_msg);
	mavlink_test_file_handshake(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // UMASSLAUNCHCOMM_TESTSUITE_H

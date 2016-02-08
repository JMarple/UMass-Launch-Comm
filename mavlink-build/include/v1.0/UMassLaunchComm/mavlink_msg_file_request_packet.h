// MESSAGE FILE_REQUEST_PACKET PACKING

#define MAVLINK_MSG_ID_FILE_REQUEST_PACKET 103

typedef struct __mavlink_file_request_packet_t
{
 uint16_t id; /*< */
 uint16_t segment; /*< */
} mavlink_file_request_packet_t;

#define MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN 4
#define MAVLINK_MSG_ID_103_LEN 4

#define MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC 92
#define MAVLINK_MSG_ID_103_CRC 92



#define MAVLINK_MESSAGE_INFO_FILE_REQUEST_PACKET { \
	"FILE_REQUEST_PACKET", \
	2, \
	{  { "id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_file_request_packet_t, id) }, \
         { "segment", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_file_request_packet_t, segment) }, \
         } \
}


/**
 * @brief Pack a file_request_packet message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id 
 * @param segment 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_request_packet_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t id, uint16_t segment)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN];
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, segment);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#else
	mavlink_file_request_packet_t packet;
	packet.id = id;
	packet.segment = segment;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE_REQUEST_PACKET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
}

/**
 * @brief Pack a file_request_packet message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id 
 * @param segment 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_request_packet_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t id,uint16_t segment)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN];
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, segment);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#else
	mavlink_file_request_packet_t packet;
	packet.id = id;
	packet.segment = segment;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE_REQUEST_PACKET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
}

/**
 * @brief Encode a file_request_packet struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param file_request_packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_request_packet_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_file_request_packet_t* file_request_packet)
{
	return mavlink_msg_file_request_packet_pack(system_id, component_id, msg, file_request_packet->id, file_request_packet->segment);
}

/**
 * @brief Encode a file_request_packet struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param file_request_packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_request_packet_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_file_request_packet_t* file_request_packet)
{
	return mavlink_msg_file_request_packet_pack_chan(system_id, component_id, chan, msg, file_request_packet->id, file_request_packet->segment);
}

/**
 * @brief Send a file_request_packet message
 * @param chan MAVLink channel to send the message
 *
 * @param id 
 * @param segment 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_file_request_packet_send(mavlink_channel_t chan, uint16_t id, uint16_t segment)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN];
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, segment);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, buf, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, buf, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
#else
	mavlink_file_request_packet_t packet;
	packet.id = id;
	packet.segment = segment;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, (const char *)&packet, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, (const char *)&packet, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_file_request_packet_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t id, uint16_t segment)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, segment);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, buf, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, buf, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
#else
	mavlink_file_request_packet_t *packet = (mavlink_file_request_packet_t *)msgbuf;
	packet->id = id;
	packet->segment = segment;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, (const char *)packet, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_REQUEST_PACKET, (const char *)packet, MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE FILE_REQUEST_PACKET UNPACKING


/**
 * @brief Get field id from file_request_packet message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_request_packet_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field segment from file_request_packet message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_request_packet_get_segment(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a file_request_packet message into a struct
 *
 * @param msg The message to decode
 * @param file_request_packet C-struct to decode the message contents into
 */
static inline void mavlink_msg_file_request_packet_decode(const mavlink_message_t* msg, mavlink_file_request_packet_t* file_request_packet)
{
#if MAVLINK_NEED_BYTE_SWAP
	file_request_packet->id = mavlink_msg_file_request_packet_get_id(msg);
	file_request_packet->segment = mavlink_msg_file_request_packet_get_segment(msg);
#else
	memcpy(file_request_packet, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_FILE_REQUEST_PACKET_LEN);
#endif
}

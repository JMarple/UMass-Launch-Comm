// MESSAGE FILE_HANDSHAKE PACKING

#define MAVLINK_MSG_ID_FILE_HANDSHAKE 102

typedef struct __mavlink_file_handshake_t
{
 uint16_t id; /*< */
 uint16_t fileType; /*< */
} mavlink_file_handshake_t;

#define MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN 4
#define MAVLINK_MSG_ID_102_LEN 4

#define MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC 216
#define MAVLINK_MSG_ID_102_CRC 216



#define MAVLINK_MESSAGE_INFO_FILE_HANDSHAKE { \
	"FILE_HANDSHAKE", \
	2, \
	{  { "id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_file_handshake_t, id) }, \
         { "fileType", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_file_handshake_t, fileType) }, \
         } \
}


/**
 * @brief Pack a file_handshake message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id 
 * @param fileType 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_handshake_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t id, uint16_t fileType)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN];
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, fileType);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#else
	mavlink_file_handshake_t packet;
	packet.id = id;
	packet.fileType = fileType;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE_HANDSHAKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN, MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
}

/**
 * @brief Pack a file_handshake message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id 
 * @param fileType 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_handshake_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t id,uint16_t fileType)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN];
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, fileType);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#else
	mavlink_file_handshake_t packet;
	packet.id = id;
	packet.fileType = fileType;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE_HANDSHAKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN, MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
}

/**
 * @brief Encode a file_handshake struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param file_handshake C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_handshake_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_file_handshake_t* file_handshake)
{
	return mavlink_msg_file_handshake_pack(system_id, component_id, msg, file_handshake->id, file_handshake->fileType);
}

/**
 * @brief Encode a file_handshake struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param file_handshake C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_handshake_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_file_handshake_t* file_handshake)
{
	return mavlink_msg_file_handshake_pack_chan(system_id, component_id, chan, msg, file_handshake->id, file_handshake->fileType);
}

/**
 * @brief Send a file_handshake message
 * @param chan MAVLink channel to send the message
 *
 * @param id 
 * @param fileType 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_file_handshake_send(mavlink_channel_t chan, uint16_t id, uint16_t fileType)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN];
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, fileType);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, buf, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN, MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, buf, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
#else
	mavlink_file_handshake_t packet;
	packet.id = id;
	packet.fileType = fileType;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, (const char *)&packet, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN, MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, (const char *)&packet, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_file_handshake_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t id, uint16_t fileType)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, id);
	_mav_put_uint16_t(buf, 2, fileType);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, buf, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN, MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, buf, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
#else
	mavlink_file_handshake_t *packet = (mavlink_file_handshake_t *)msgbuf;
	packet->id = id;
	packet->fileType = fileType;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, (const char *)packet, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN, MAVLINK_MSG_ID_FILE_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_HANDSHAKE, (const char *)packet, MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE FILE_HANDSHAKE UNPACKING


/**
 * @brief Get field id from file_handshake message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_handshake_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field fileType from file_handshake message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_handshake_get_fileType(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a file_handshake message into a struct
 *
 * @param msg The message to decode
 * @param file_handshake C-struct to decode the message contents into
 */
static inline void mavlink_msg_file_handshake_decode(const mavlink_message_t* msg, mavlink_file_handshake_t* file_handshake)
{
#if MAVLINK_NEED_BYTE_SWAP
	file_handshake->id = mavlink_msg_file_handshake_get_id(msg);
	file_handshake->fileType = mavlink_msg_file_handshake_get_fileType(msg);
#else
	memcpy(file_handshake, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_FILE_HANDSHAKE_LEN);
#endif
}

// MESSAGE FILE PACKING

#define MAVLINK_MSG_ID_FILE 101

typedef struct __mavlink_file_t
{
 uint32_t fileSize; /*< */
 uint16_t segment; /*< */
 uint16_t id; /*< */
 uint16_t bytes; /*< */
 char data[42]; /*< */
} mavlink_file_t;

#define MAVLINK_MSG_ID_FILE_LEN 52
#define MAVLINK_MSG_ID_101_LEN 52

#define MAVLINK_MSG_ID_FILE_CRC 111
#define MAVLINK_MSG_ID_101_CRC 111

#define MAVLINK_MSG_FILE_FIELD_DATA_LEN 42

#define MAVLINK_MESSAGE_INFO_FILE { \
	"FILE", \
	5, \
	{  { "fileSize", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_file_t, fileSize) }, \
         { "segment", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_file_t, segment) }, \
         { "id", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_file_t, id) }, \
         { "bytes", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_file_t, bytes) }, \
         { "data", NULL, MAVLINK_TYPE_CHAR, 42, 10, offsetof(mavlink_file_t, data) }, \
         } \
}


/**
 * @brief Pack a file message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param segment 
 * @param id 
 * @param fileSize 
 * @param bytes 
 * @param data 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t segment, uint16_t id, uint32_t fileSize, uint16_t bytes, const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_LEN];
	_mav_put_uint32_t(buf, 0, fileSize);
	_mav_put_uint16_t(buf, 4, segment);
	_mav_put_uint16_t(buf, 6, id);
	_mav_put_uint16_t(buf, 8, bytes);
	_mav_put_char_array(buf, 10, data, 42);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_LEN);
#else
	mavlink_file_t packet;
	packet.fileSize = fileSize;
	packet.segment = segment;
	packet.id = id;
	packet.bytes = bytes;
	mav_array_memcpy(packet.data, data, sizeof(char)*42);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_LEN, MAVLINK_MSG_ID_FILE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_LEN);
#endif
}

/**
 * @brief Pack a file message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param segment 
 * @param id 
 * @param fileSize 
 * @param bytes 
 * @param data 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t segment,uint16_t id,uint32_t fileSize,uint16_t bytes,const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_LEN];
	_mav_put_uint32_t(buf, 0, fileSize);
	_mav_put_uint16_t(buf, 4, segment);
	_mav_put_uint16_t(buf, 6, id);
	_mav_put_uint16_t(buf, 8, bytes);
	_mav_put_char_array(buf, 10, data, 42);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_LEN);
#else
	mavlink_file_t packet;
	packet.fileSize = fileSize;
	packet.segment = segment;
	packet.id = id;
	packet.bytes = bytes;
	mav_array_memcpy(packet.data, data, sizeof(char)*42);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_LEN, MAVLINK_MSG_ID_FILE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_LEN);
#endif
}

/**
 * @brief Encode a file struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param file C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_file_t* file)
{
	return mavlink_msg_file_pack(system_id, component_id, msg, file->segment, file->id, file->fileSize, file->bytes, file->data);
}

/**
 * @brief Encode a file struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param file C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_file_t* file)
{
	return mavlink_msg_file_pack_chan(system_id, component_id, chan, msg, file->segment, file->id, file->fileSize, file->bytes, file->data);
}

/**
 * @brief Send a file message
 * @param chan MAVLink channel to send the message
 *
 * @param segment 
 * @param id 
 * @param fileSize 
 * @param bytes 
 * @param data 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_file_send(mavlink_channel_t chan, uint16_t segment, uint16_t id, uint32_t fileSize, uint16_t bytes, const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_LEN];
	_mav_put_uint32_t(buf, 0, fileSize);
	_mav_put_uint16_t(buf, 4, segment);
	_mav_put_uint16_t(buf, 6, id);
	_mav_put_uint16_t(buf, 8, bytes);
	_mav_put_char_array(buf, 10, data, 42);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, buf, MAVLINK_MSG_ID_FILE_LEN, MAVLINK_MSG_ID_FILE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, buf, MAVLINK_MSG_ID_FILE_LEN);
#endif
#else
	mavlink_file_t packet;
	packet.fileSize = fileSize;
	packet.segment = segment;
	packet.id = id;
	packet.bytes = bytes;
	mav_array_memcpy(packet.data, data, sizeof(char)*42);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, (const char *)&packet, MAVLINK_MSG_ID_FILE_LEN, MAVLINK_MSG_ID_FILE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, (const char *)&packet, MAVLINK_MSG_ID_FILE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_FILE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_file_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t segment, uint16_t id, uint32_t fileSize, uint16_t bytes, const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, fileSize);
	_mav_put_uint16_t(buf, 4, segment);
	_mav_put_uint16_t(buf, 6, id);
	_mav_put_uint16_t(buf, 8, bytes);
	_mav_put_char_array(buf, 10, data, 42);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, buf, MAVLINK_MSG_ID_FILE_LEN, MAVLINK_MSG_ID_FILE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, buf, MAVLINK_MSG_ID_FILE_LEN);
#endif
#else
	mavlink_file_t *packet = (mavlink_file_t *)msgbuf;
	packet->fileSize = fileSize;
	packet->segment = segment;
	packet->id = id;
	packet->bytes = bytes;
	mav_array_memcpy(packet->data, data, sizeof(char)*42);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, (const char *)packet, MAVLINK_MSG_ID_FILE_LEN, MAVLINK_MSG_ID_FILE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE, (const char *)packet, MAVLINK_MSG_ID_FILE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE FILE UNPACKING


/**
 * @brief Get field segment from file message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_get_segment(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field id from file message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field fileSize from file message
 *
 * @return 
 */
static inline uint32_t mavlink_msg_file_get_fileSize(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field bytes from file message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_get_bytes(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field data from file message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_get_data(const mavlink_message_t* msg, char *data)
{
	return _MAV_RETURN_char_array(msg, data, 42,  10);
}

/**
 * @brief Decode a file message into a struct
 *
 * @param msg The message to decode
 * @param file C-struct to decode the message contents into
 */
static inline void mavlink_msg_file_decode(const mavlink_message_t* msg, mavlink_file_t* file)
{
#if MAVLINK_NEED_BYTE_SWAP
	file->fileSize = mavlink_msg_file_get_fileSize(msg);
	file->segment = mavlink_msg_file_get_segment(msg);
	file->id = mavlink_msg_file_get_id(msg);
	file->bytes = mavlink_msg_file_get_bytes(msg);
	mavlink_msg_file_get_data(msg, file->data);
#else
	memcpy(file, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_FILE_LEN);
#endif
}

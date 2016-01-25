// MESSAGE IMAGE PACKING

#define MAVLINK_MSG_ID_IMAGE 101

typedef struct __mavlink_image_t
{
 uint16_t segment; /*< */
 uint16_t image; /*< */
 uint16_t numSegments; /*< */
 uint16_t bytes; /*< */
 char data[200]; /*< */
} mavlink_image_t;

#define MAVLINK_MSG_ID_IMAGE_LEN 208
#define MAVLINK_MSG_ID_101_LEN 208

#define MAVLINK_MSG_ID_IMAGE_CRC 83
#define MAVLINK_MSG_ID_101_CRC 83

#define MAVLINK_MSG_IMAGE_FIELD_DATA_LEN 200

#define MAVLINK_MESSAGE_INFO_IMAGE { \
	"IMAGE", \
	5, \
	{  { "segment", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_image_t, segment) }, \
         { "image", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_image_t, image) }, \
         { "numSegments", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_image_t, numSegments) }, \
         { "bytes", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_image_t, bytes) }, \
         { "data", NULL, MAVLINK_TYPE_CHAR, 200, 8, offsetof(mavlink_image_t, data) }, \
         } \
}


/**
 * @brief Pack a image message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param segment 
 * @param image 
 * @param numSegments 
 * @param bytes 
 * @param data 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_image_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t segment, uint16_t image, uint16_t numSegments, uint16_t bytes, const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_IMAGE_LEN];
	_mav_put_uint16_t(buf, 0, segment);
	_mav_put_uint16_t(buf, 2, image);
	_mav_put_uint16_t(buf, 4, numSegments);
	_mav_put_uint16_t(buf, 6, bytes);
	_mav_put_char_array(buf, 8, data, 200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMAGE_LEN);
#else
	mavlink_image_t packet;
	packet.segment = segment;
	packet.image = image;
	packet.numSegments = numSegments;
	packet.bytes = bytes;
	mav_array_memcpy(packet.data, data, sizeof(char)*200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMAGE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_IMAGE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_IMAGE_LEN, MAVLINK_MSG_ID_IMAGE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_IMAGE_LEN);
#endif
}

/**
 * @brief Pack a image message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param segment 
 * @param image 
 * @param numSegments 
 * @param bytes 
 * @param data 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_image_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t segment,uint16_t image,uint16_t numSegments,uint16_t bytes,const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_IMAGE_LEN];
	_mav_put_uint16_t(buf, 0, segment);
	_mav_put_uint16_t(buf, 2, image);
	_mav_put_uint16_t(buf, 4, numSegments);
	_mav_put_uint16_t(buf, 6, bytes);
	_mav_put_char_array(buf, 8, data, 200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMAGE_LEN);
#else
	mavlink_image_t packet;
	packet.segment = segment;
	packet.image = image;
	packet.numSegments = numSegments;
	packet.bytes = bytes;
	mav_array_memcpy(packet.data, data, sizeof(char)*200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMAGE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_IMAGE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_IMAGE_LEN, MAVLINK_MSG_ID_IMAGE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_IMAGE_LEN);
#endif
}

/**
 * @brief Encode a image struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param image C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_image_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_image_t* image)
{
	return mavlink_msg_image_pack(system_id, component_id, msg, image->segment, image->image, image->numSegments, image->bytes, image->data);
}

/**
 * @brief Encode a image struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param image C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_image_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_image_t* image)
{
	return mavlink_msg_image_pack_chan(system_id, component_id, chan, msg, image->segment, image->image, image->numSegments, image->bytes, image->data);
}

/**
 * @brief Send a image message
 * @param chan MAVLink channel to send the message
 *
 * @param segment 
 * @param image 
 * @param numSegments 
 * @param bytes 
 * @param data 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_image_send(mavlink_channel_t chan, uint16_t segment, uint16_t image, uint16_t numSegments, uint16_t bytes, const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_IMAGE_LEN];
	_mav_put_uint16_t(buf, 0, segment);
	_mav_put_uint16_t(buf, 2, image);
	_mav_put_uint16_t(buf, 4, numSegments);
	_mav_put_uint16_t(buf, 6, bytes);
	_mav_put_char_array(buf, 8, data, 200);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, buf, MAVLINK_MSG_ID_IMAGE_LEN, MAVLINK_MSG_ID_IMAGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, buf, MAVLINK_MSG_ID_IMAGE_LEN);
#endif
#else
	mavlink_image_t packet;
	packet.segment = segment;
	packet.image = image;
	packet.numSegments = numSegments;
	packet.bytes = bytes;
	mav_array_memcpy(packet.data, data, sizeof(char)*200);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, (const char *)&packet, MAVLINK_MSG_ID_IMAGE_LEN, MAVLINK_MSG_ID_IMAGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, (const char *)&packet, MAVLINK_MSG_ID_IMAGE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_IMAGE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_image_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t segment, uint16_t image, uint16_t numSegments, uint16_t bytes, const char *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, segment);
	_mav_put_uint16_t(buf, 2, image);
	_mav_put_uint16_t(buf, 4, numSegments);
	_mav_put_uint16_t(buf, 6, bytes);
	_mav_put_char_array(buf, 8, data, 200);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, buf, MAVLINK_MSG_ID_IMAGE_LEN, MAVLINK_MSG_ID_IMAGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, buf, MAVLINK_MSG_ID_IMAGE_LEN);
#endif
#else
	mavlink_image_t *packet = (mavlink_image_t *)msgbuf;
	packet->segment = segment;
	packet->image = image;
	packet->numSegments = numSegments;
	packet->bytes = bytes;
	mav_array_memcpy(packet->data, data, sizeof(char)*200);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, (const char *)packet, MAVLINK_MSG_ID_IMAGE_LEN, MAVLINK_MSG_ID_IMAGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMAGE, (const char *)packet, MAVLINK_MSG_ID_IMAGE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE IMAGE UNPACKING


/**
 * @brief Get field segment from image message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_image_get_segment(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field image from image message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_image_get_image(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field numSegments from image message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_image_get_numSegments(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field bytes from image message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_image_get_bytes(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field data from image message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_image_get_data(const mavlink_message_t* msg, char *data)
{
	return _MAV_RETURN_char_array(msg, data, 200,  8);
}

/**
 * @brief Decode a image message into a struct
 *
 * @param msg The message to decode
 * @param image C-struct to decode the message contents into
 */
static inline void mavlink_msg_image_decode(const mavlink_message_t* msg, mavlink_image_t* image)
{
#if MAVLINK_NEED_BYTE_SWAP
	image->segment = mavlink_msg_image_get_segment(msg);
	image->image = mavlink_msg_image_get_image(msg);
	image->numSegments = mavlink_msg_image_get_numSegments(msg);
	image->bytes = mavlink_msg_image_get_bytes(msg);
	mavlink_msg_image_get_data(msg, image->data);
#else
	memcpy(image, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_IMAGE_LEN);
#endif
}

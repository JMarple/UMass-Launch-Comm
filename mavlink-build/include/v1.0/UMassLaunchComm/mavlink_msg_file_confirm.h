// MESSAGE FILE_CONFIRM PACKING

#define MAVLINK_MSG_ID_FILE_CONFIRM 104

typedef struct __mavlink_file_confirm_t
{
 uint16_t id; /*< */
} mavlink_file_confirm_t;

#define MAVLINK_MSG_ID_FILE_CONFIRM_LEN 2
#define MAVLINK_MSG_ID_104_LEN 2

#define MAVLINK_MSG_ID_FILE_CONFIRM_CRC 51
#define MAVLINK_MSG_ID_104_CRC 51



#define MAVLINK_MESSAGE_INFO_FILE_CONFIRM { \
	"FILE_CONFIRM", \
	1, \
	{  { "id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_file_confirm_t, id) }, \
         } \
}


/**
 * @brief Pack a file_confirm message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_confirm_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_CONFIRM_LEN];
	_mav_put_uint16_t(buf, 0, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#else
	mavlink_file_confirm_t packet;
	packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE_CONFIRM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_CONFIRM_LEN, MAVLINK_MSG_ID_FILE_CONFIRM_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
}

/**
 * @brief Pack a file_confirm message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_file_confirm_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_CONFIRM_LEN];
	_mav_put_uint16_t(buf, 0, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#else
	mavlink_file_confirm_t packet;
	packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_FILE_CONFIRM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_CONFIRM_LEN, MAVLINK_MSG_ID_FILE_CONFIRM_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
}

/**
 * @brief Encode a file_confirm struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param file_confirm C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_confirm_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_file_confirm_t* file_confirm)
{
	return mavlink_msg_file_confirm_pack(system_id, component_id, msg, file_confirm->id);
}

/**
 * @brief Encode a file_confirm struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param file_confirm C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_file_confirm_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_file_confirm_t* file_confirm)
{
	return mavlink_msg_file_confirm_pack_chan(system_id, component_id, chan, msg, file_confirm->id);
}

/**
 * @brief Send a file_confirm message
 * @param chan MAVLink channel to send the message
 *
 * @param id 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_file_confirm_send(mavlink_channel_t chan, uint16_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_FILE_CONFIRM_LEN];
	_mav_put_uint16_t(buf, 0, id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, buf, MAVLINK_MSG_ID_FILE_CONFIRM_LEN, MAVLINK_MSG_ID_FILE_CONFIRM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, buf, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
#else
	mavlink_file_confirm_t packet;
	packet.id = id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, (const char *)&packet, MAVLINK_MSG_ID_FILE_CONFIRM_LEN, MAVLINK_MSG_ID_FILE_CONFIRM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, (const char *)&packet, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_FILE_CONFIRM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_file_confirm_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, buf, MAVLINK_MSG_ID_FILE_CONFIRM_LEN, MAVLINK_MSG_ID_FILE_CONFIRM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, buf, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
#else
	mavlink_file_confirm_t *packet = (mavlink_file_confirm_t *)msgbuf;
	packet->id = id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, (const char *)packet, MAVLINK_MSG_ID_FILE_CONFIRM_LEN, MAVLINK_MSG_ID_FILE_CONFIRM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FILE_CONFIRM, (const char *)packet, MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE FILE_CONFIRM UNPACKING


/**
 * @brief Get field id from file_confirm message
 *
 * @return 
 */
static inline uint16_t mavlink_msg_file_confirm_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a file_confirm message into a struct
 *
 * @param msg The message to decode
 * @param file_confirm C-struct to decode the message contents into
 */
static inline void mavlink_msg_file_confirm_decode(const mavlink_message_t* msg, mavlink_file_confirm_t* file_confirm)
{
#if MAVLINK_NEED_BYTE_SWAP
	file_confirm->id = mavlink_msg_file_confirm_get_id(msg);
#else
	memcpy(file_confirm, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_FILE_CONFIRM_LEN);
#endif
}

// MESSAGE HANDSHAKE PACKING

#define MAVLINK_MSG_ID_HANDSHAKE 1

typedef struct __mavlink_handshake_t
{
 uint8_t id; /*< */
} mavlink_handshake_t;

#define MAVLINK_MSG_ID_HANDSHAKE_LEN 1
#define MAVLINK_MSG_ID_1_LEN 1

#define MAVLINK_MSG_ID_HANDSHAKE_CRC 209
#define MAVLINK_MSG_ID_1_CRC 209



#define MAVLINK_MESSAGE_INFO_HANDSHAKE { \
	"HANDSHAKE", \
	1, \
	{  { "id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_handshake_t, id) }, \
         } \
}


/**
 * @brief Pack a handshake message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_handshake_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HANDSHAKE_LEN];
	_mav_put_uint8_t(buf, 0, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#else
	mavlink_handshake_t packet;
	packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_HANDSHAKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HANDSHAKE_LEN, MAVLINK_MSG_ID_HANDSHAKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
}

/**
 * @brief Pack a handshake message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_handshake_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HANDSHAKE_LEN];
	_mav_put_uint8_t(buf, 0, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#else
	mavlink_handshake_t packet;
	packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_HANDSHAKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HANDSHAKE_LEN, MAVLINK_MSG_ID_HANDSHAKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
}

/**
 * @brief Encode a handshake struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param handshake C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_handshake_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_handshake_t* handshake)
{
	return mavlink_msg_handshake_pack(system_id, component_id, msg, handshake->id);
}

/**
 * @brief Encode a handshake struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param handshake C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_handshake_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_handshake_t* handshake)
{
	return mavlink_msg_handshake_pack_chan(system_id, component_id, chan, msg, handshake->id);
}

/**
 * @brief Send a handshake message
 * @param chan MAVLink channel to send the message
 *
 * @param id 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_handshake_send(mavlink_channel_t chan, uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HANDSHAKE_LEN];
	_mav_put_uint8_t(buf, 0, id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, buf, MAVLINK_MSG_ID_HANDSHAKE_LEN, MAVLINK_MSG_ID_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, buf, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
#else
	mavlink_handshake_t packet;
	packet.id = id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, (const char *)&packet, MAVLINK_MSG_ID_HANDSHAKE_LEN, MAVLINK_MSG_ID_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, (const char *)&packet, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_HANDSHAKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_handshake_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, buf, MAVLINK_MSG_ID_HANDSHAKE_LEN, MAVLINK_MSG_ID_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, buf, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
#else
	mavlink_handshake_t *packet = (mavlink_handshake_t *)msgbuf;
	packet->id = id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, (const char *)packet, MAVLINK_MSG_ID_HANDSHAKE_LEN, MAVLINK_MSG_ID_HANDSHAKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HANDSHAKE, (const char *)packet, MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE HANDSHAKE UNPACKING


/**
 * @brief Get field id from handshake message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_handshake_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a handshake message into a struct
 *
 * @param msg The message to decode
 * @param handshake C-struct to decode the message contents into
 */
static inline void mavlink_msg_handshake_decode(const mavlink_message_t* msg, mavlink_handshake_t* handshake)
{
#if MAVLINK_NEED_BYTE_SWAP
	handshake->id = mavlink_msg_handshake_get_id(msg);
#else
	memcpy(handshake, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_HANDSHAKE_LEN);
#endif
}

// MESSAGE AIR_DATA PACKING

#define MAVLINK_MSG_ID_AIR_DATA 171

typedef struct __mavlink_air_data_t
{
 float dynamicPressure; /*< Dynamic pressure (Pa)*/
 float staticPressure; /*< Static pressure (Pa)*/
 uint16_t temperature; /*< Board temperature*/
} mavlink_air_data_t;

#define MAVLINK_MSG_ID_AIR_DATA_LEN 10
#define MAVLINK_MSG_ID_171_LEN 10

#define MAVLINK_MSG_ID_AIR_DATA_CRC 232
#define MAVLINK_MSG_ID_171_CRC 232



#define MAVLINK_MESSAGE_INFO_AIR_DATA { \
	"AIR_DATA", \
	3, \
	{  { "dynamicPressure", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_air_data_t, dynamicPressure) }, \
         { "staticPressure", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_air_data_t, staticPressure) }, \
         { "temperature", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_air_data_t, temperature) }, \
         } \
}


/**
 * @brief Pack a air_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param dynamicPressure Dynamic pressure (Pa)
 * @param staticPressure Static pressure (Pa)
 * @param temperature Board temperature
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_air_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float dynamicPressure, float staticPressure, uint16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_AIR_DATA_LEN];
	_mav_put_float(buf, 0, dynamicPressure);
	_mav_put_float(buf, 4, staticPressure);
	_mav_put_uint16_t(buf, 8, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AIR_DATA_LEN);
#else
	mavlink_air_data_t packet;
	packet.dynamicPressure = dynamicPressure;
	packet.staticPressure = staticPressure;
	packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_AIR_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AIR_DATA_LEN, MAVLINK_MSG_ID_AIR_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
}

/**
 * @brief Pack a air_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dynamicPressure Dynamic pressure (Pa)
 * @param staticPressure Static pressure (Pa)
 * @param temperature Board temperature
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_air_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float dynamicPressure,float staticPressure,uint16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_AIR_DATA_LEN];
	_mav_put_float(buf, 0, dynamicPressure);
	_mav_put_float(buf, 4, staticPressure);
	_mav_put_uint16_t(buf, 8, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AIR_DATA_LEN);
#else
	mavlink_air_data_t packet;
	packet.dynamicPressure = dynamicPressure;
	packet.staticPressure = staticPressure;
	packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_AIR_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AIR_DATA_LEN, MAVLINK_MSG_ID_AIR_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
}

/**
 * @brief Encode a air_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param air_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_air_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_air_data_t* air_data)
{
	return mavlink_msg_air_data_pack(system_id, component_id, msg, air_data->dynamicPressure, air_data->staticPressure, air_data->temperature);
}

/**
 * @brief Encode a air_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param air_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_air_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_air_data_t* air_data)
{
	return mavlink_msg_air_data_pack_chan(system_id, component_id, chan, msg, air_data->dynamicPressure, air_data->staticPressure, air_data->temperature);
}

/**
 * @brief Send a air_data message
 * @param chan MAVLink channel to send the message
 *
 * @param dynamicPressure Dynamic pressure (Pa)
 * @param staticPressure Static pressure (Pa)
 * @param temperature Board temperature
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_air_data_send(mavlink_channel_t chan, float dynamicPressure, float staticPressure, uint16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_AIR_DATA_LEN];
	_mav_put_float(buf, 0, dynamicPressure);
	_mav_put_float(buf, 4, staticPressure);
	_mav_put_uint16_t(buf, 8, temperature);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, buf, MAVLINK_MSG_ID_AIR_DATA_LEN, MAVLINK_MSG_ID_AIR_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, buf, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
#else
	mavlink_air_data_t packet;
	packet.dynamicPressure = dynamicPressure;
	packet.staticPressure = staticPressure;
	packet.temperature = temperature;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, (const char *)&packet, MAVLINK_MSG_ID_AIR_DATA_LEN, MAVLINK_MSG_ID_AIR_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, (const char *)&packet, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_AIR_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_air_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float dynamicPressure, float staticPressure, uint16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, dynamicPressure);
	_mav_put_float(buf, 4, staticPressure);
	_mav_put_uint16_t(buf, 8, temperature);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, buf, MAVLINK_MSG_ID_AIR_DATA_LEN, MAVLINK_MSG_ID_AIR_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, buf, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
#else
	mavlink_air_data_t *packet = (mavlink_air_data_t *)msgbuf;
	packet->dynamicPressure = dynamicPressure;
	packet->staticPressure = staticPressure;
	packet->temperature = temperature;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, (const char *)packet, MAVLINK_MSG_ID_AIR_DATA_LEN, MAVLINK_MSG_ID_AIR_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AIR_DATA, (const char *)packet, MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE AIR_DATA UNPACKING


/**
 * @brief Get field dynamicPressure from air_data message
 *
 * @return Dynamic pressure (Pa)
 */
static inline float mavlink_msg_air_data_get_dynamicPressure(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field staticPressure from air_data message
 *
 * @return Static pressure (Pa)
 */
static inline float mavlink_msg_air_data_get_staticPressure(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field temperature from air_data message
 *
 * @return Board temperature
 */
static inline uint16_t mavlink_msg_air_data_get_temperature(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Decode a air_data message into a struct
 *
 * @param msg The message to decode
 * @param air_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_air_data_decode(const mavlink_message_t* msg, mavlink_air_data_t* air_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	air_data->dynamicPressure = mavlink_msg_air_data_get_dynamicPressure(msg);
	air_data->staticPressure = mavlink_msg_air_data_get_staticPressure(msg);
	air_data->temperature = mavlink_msg_air_data_get_temperature(msg);
#else
	memcpy(air_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_AIR_DATA_LEN);
#endif
}

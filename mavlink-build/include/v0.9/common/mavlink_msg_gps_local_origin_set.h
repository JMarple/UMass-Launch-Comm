// MESSAGE GPS_LOCAL_ORIGIN_SET PACKING

#define MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET 49

typedef struct __mavlink_gps_local_origin_set_t
{
 int32_t latitude; /*< Latitude (WGS84), expressed as * 1E7*/
 int32_t longitude; /*< Longitude (WGS84), expressed as * 1E7*/
 int32_t altitude; /*< Altitude(WGS84), expressed as * 1000*/
} mavlink_gps_local_origin_set_t;

#define MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN 12
#define MAVLINK_MSG_ID_49_LEN 12

#define MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC 14
#define MAVLINK_MSG_ID_49_CRC 14



#define MAVLINK_MESSAGE_INFO_GPS_LOCAL_ORIGIN_SET { \
	"GPS_LOCAL_ORIGIN_SET", \
	3, \
	{  { "latitude", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_gps_local_origin_set_t, latitude) }, \
         { "longitude", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_gps_local_origin_set_t, longitude) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_gps_local_origin_set_t, altitude) }, \
         } \
}


/**
 * @brief Pack a gps_local_origin_set message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param latitude Latitude (WGS84), expressed as * 1E7
 * @param longitude Longitude (WGS84), expressed as * 1E7
 * @param altitude Altitude(WGS84), expressed as * 1000
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int32_t latitude, int32_t longitude, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN];
	_mav_put_int32_t(buf, 0, latitude);
	_mav_put_int32_t(buf, 4, longitude);
	_mav_put_int32_t(buf, 8, altitude);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#else
	mavlink_gps_local_origin_set_t packet;
	packet.latitude = latitude;
	packet.longitude = longitude;
	packet.altitude = altitude;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
}

/**
 * @brief Pack a gps_local_origin_set message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param latitude Latitude (WGS84), expressed as * 1E7
 * @param longitude Longitude (WGS84), expressed as * 1E7
 * @param altitude Altitude(WGS84), expressed as * 1000
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int32_t latitude,int32_t longitude,int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN];
	_mav_put_int32_t(buf, 0, latitude);
	_mav_put_int32_t(buf, 4, longitude);
	_mav_put_int32_t(buf, 8, altitude);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#else
	mavlink_gps_local_origin_set_t packet;
	packet.latitude = latitude;
	packet.longitude = longitude;
	packet.altitude = altitude;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
}

/**
 * @brief Encode a gps_local_origin_set struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps_local_origin_set C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_local_origin_set_t* gps_local_origin_set)
{
	return mavlink_msg_gps_local_origin_set_pack(system_id, component_id, msg, gps_local_origin_set->latitude, gps_local_origin_set->longitude, gps_local_origin_set->altitude);
}

/**
 * @brief Encode a gps_local_origin_set struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gps_local_origin_set C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gps_local_origin_set_t* gps_local_origin_set)
{
	return mavlink_msg_gps_local_origin_set_pack_chan(system_id, component_id, chan, msg, gps_local_origin_set->latitude, gps_local_origin_set->longitude, gps_local_origin_set->altitude);
}

/**
 * @brief Send a gps_local_origin_set message
 * @param chan MAVLink channel to send the message
 *
 * @param latitude Latitude (WGS84), expressed as * 1E7
 * @param longitude Longitude (WGS84), expressed as * 1E7
 * @param altitude Altitude(WGS84), expressed as * 1000
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_local_origin_set_send(mavlink_channel_t chan, int32_t latitude, int32_t longitude, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN];
	_mav_put_int32_t(buf, 0, latitude);
	_mav_put_int32_t(buf, 4, longitude);
	_mav_put_int32_t(buf, 8, altitude);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, buf, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, buf, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
#else
	mavlink_gps_local_origin_set_t packet;
	packet.latitude = latitude;
	packet.longitude = longitude;
	packet.altitude = altitude;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, (const char *)&packet, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, (const char *)&packet, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gps_local_origin_set_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int32_t latitude, int32_t longitude, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_int32_t(buf, 0, latitude);
	_mav_put_int32_t(buf, 4, longitude);
	_mav_put_int32_t(buf, 8, altitude);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, buf, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, buf, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
#else
	mavlink_gps_local_origin_set_t *packet = (mavlink_gps_local_origin_set_t *)msgbuf;
	packet->latitude = latitude;
	packet->longitude = longitude;
	packet->altitude = altitude;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, (const char *)packet, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET, (const char *)packet, MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE GPS_LOCAL_ORIGIN_SET UNPACKING


/**
 * @brief Get field latitude from gps_local_origin_set message
 *
 * @return Latitude (WGS84), expressed as * 1E7
 */
static inline int32_t mavlink_msg_gps_local_origin_set_get_latitude(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field longitude from gps_local_origin_set message
 *
 * @return Longitude (WGS84), expressed as * 1E7
 */
static inline int32_t mavlink_msg_gps_local_origin_set_get_longitude(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field altitude from gps_local_origin_set message
 *
 * @return Altitude(WGS84), expressed as * 1000
 */
static inline int32_t mavlink_msg_gps_local_origin_set_get_altitude(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Decode a gps_local_origin_set message into a struct
 *
 * @param msg The message to decode
 * @param gps_local_origin_set C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_local_origin_set_decode(const mavlink_message_t* msg, mavlink_gps_local_origin_set_t* gps_local_origin_set)
{
#if MAVLINK_NEED_BYTE_SWAP
	gps_local_origin_set->latitude = mavlink_msg_gps_local_origin_set_get_latitude(msg);
	gps_local_origin_set->longitude = mavlink_msg_gps_local_origin_set_get_longitude(msg);
	gps_local_origin_set->altitude = mavlink_msg_gps_local_origin_set_get_altitude(msg);
#else
	memcpy(gps_local_origin_set, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET_LEN);
#endif
}

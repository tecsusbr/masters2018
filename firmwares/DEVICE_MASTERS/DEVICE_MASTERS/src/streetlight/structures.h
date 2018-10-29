#ifndef STRUCTURES_H_
#define STRUCTURES_H_

COMPILER_PACK_SET(1)
typedef enum PacketType_t {
	PACKET_COMMAND,
	PACKET_DATA,
	PACKET_PING,
} PacketType_t;

typedef struct AppPacket_t {
	uint16_t unique_id;
	uint16_t short_addr;
	uint16_t parent_addr;
	uint8_t packet_type;
	uint8_t light;
	uint8_t temp;
	uint8_t hum;
	uint8_t refresh_rate;
} AppPacket_t;

typedef enum AppState_t {
	APP_STATE_INITIAL,
	APP_STATE_START_NETWORK,
	APP_STATE_CONNECT_NETWORK,
	APP_STATE_CONNECTING_NETWORK,
	APP_STATE_IN_NETWORK,
	APP_STATE_SEND,
	APP_STATE_WAIT_CONF,
	APP_STATE_SENDING_DONE,
	APP_STATE_WAIT_SEND_TIMER,
	APP_STATE_WAIT_COMMAND_TIMER,
	APP_STATE_PREPARE_TO_SLEEP,
	APP_STATE_SLEEP,
	APP_STATE_WAKEUP,
	
	/* CUSTOMS STATES */
	APP_STATE_NO_DEFINED,
	APP_STATE_SEND_CMD,
} AppState_t;
COMPILER_PACK_RESET()


#endif /* STRUCTURES_H_ */
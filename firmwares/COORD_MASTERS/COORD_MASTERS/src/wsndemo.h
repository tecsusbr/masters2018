#ifndef WSNDEMO_H
#define WSNDEMO_H

#include "board.h"
#include "sysTimer.h"

#define APP_SERIAL_CMD_SIZE		4

void wsndemo_init(void);
void wsndemo_task(void);

#ifndef LED_COUNT
#define LED_COUNT 0
#endif

#if LED_COUNT > 2
#define LED_NETWORK       LED0_GPIO
#define LED_DATA          LED1_GPIO
#define LED_BLINK         LED2_GPIO
#define LED_IDENTIFY      LED0_GPIO
#elif LED_COUNT == 2
#define LED_NETWORK       LED0_GPIO
#define LED_DATA          LED1_GPIO
#define LED_BLINK         LED1_GPIO
#define LED_IDENTIFY      LED0_GPIO
#elif LED_COUNT == 1
#define LED_NETWORK       LED0_GPIO
#define LED_DATA          LED0_GPIO
#define LED_BLINK         LED0_GPIO
#define LED_IDENTIFY      LED0_GPIO
#endif

#ifdef LED0_ACTIVE_LEVEL
#define LED_NETWORK_GPIO       LED0_GPIO
#define LED_DATA_GPIO          LED0_GPIO
#define LED_BLINK_GPIO         LED0_GPIO
#define LED_IDENTIFY_GPIO      LED0_GPIO
#define LED_IDENTIFY_ACTIVE_LEVEL  LED0_ACTIVE_LEVEL
#define LED_IDENTIFY_INACTIVE_LEVEL  LED0_ACTIVE_LEVEL
#define LED_NETWORK_ACTIVE_LEVEL  LED0_INACTIVE_LEVEL
#define LED_NETWORK_INACTIVE_LEVEL  LED0_INACTIVE_LEVEL
#define LED_DATA_ACTIVE_LEVEL  LED0_ACTIVE_LEVEL
#define LED_DATA_INACTIVE_LEVEL  LED0_INACTIVE_LEVEL
#define LED_BLINK_ACTIVE_LEVEL  LED0_ACTIVE_LEVEL
#define LED_BLINK_INACTIVE_LEVEL  LED0_INACTIVE_LEVEL
#endif

#define MIN_SLEEP_INTERVAL 500

extern SYS_Timer_t appDataSendingTimer;

#endif /* WSNDEMO_H */

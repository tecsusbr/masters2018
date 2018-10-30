#ifndef STREETLIGHT_H_
#define STREETLIGHT_H_
#include "board.h"
#include "sysTimer.h"

/* Your information here */
#define UNIQUE_ID				2		// Unique ID
#define TRANSMISSION_TIME		30		// In seconds
#define APP_SCAN_DURATION 10
void strlight_init(void);
void strlight_task(void);

#endif /* STREETLIGHT_H_ */
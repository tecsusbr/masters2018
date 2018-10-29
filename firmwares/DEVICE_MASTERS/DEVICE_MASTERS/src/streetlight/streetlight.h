#ifndef STREETLIGHT_H_
#define STREETLIGHT_H_
#include "board.h"
#include "sysTimer.h"

#define UNIQUE_ID	1

#define APP_SCAN_DURATION 10
void strlight_init(void);
void strlight_task(void);

#endif /* STREETLIGHT_H_ */

/************************ HEADERS ****************************************/
#include "asf.h"
#include "sio2host.h"
#include "streetlight.h"
#include "miwi_api.h"

#include "edbg-eui.h"

int main ( void )
{
	irq_initialize_vectors();

	system_init();
	delay_init();

	cpu_irq_enable();	
	
	sio2host_init();
    /* Initialize system Timer */
    SYS_TimerInit();

    /* Initialize the demo */
	strlight_init();

    while(1)
    {
		strlight_task();
    }
}


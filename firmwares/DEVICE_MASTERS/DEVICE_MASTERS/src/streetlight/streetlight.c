#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "phy.h"
#include "sysTimer.h"
#include "structures.h"
#include "miwi_api.h"

#include "system.h"

#include "asf.h"
#include "streetlight.h"

/*- Variables --------------------------------------------------------------*/
static AppState_t appState = APP_STATE_INITIAL;

static bool appNetworkStatus;

static AppPacket_t appMsg;
SYS_Timer_t appDataSendingTimer;
static uint8_t wsnmsghandle;
static uint8_t try_again = 0x0;

void UartBytesReceived(uint16_t bytes, uint8_t *byte );
static void Connection_Confirm(miwi_status_t status);

void searchConfim(uint8_t foundScanResults, void* ScanResults);
void appLinkFailureCallback(void);

bool reconnectStatus = false;
/*- Implementations --------------------------------------------------------*/

static void appDataInd(RECEIVED_MESH_MESSAGE *ind)
{
	AppPacket_t *msg = (AppPacket_t *)ind->payload;
	/* Received Message */
	/* Your code here... */
	
}

/*****************************************************************************
*****************************************************************************/
static void appDataSendingTimerHandler(SYS_Timer_t *timer)
{
	if (APP_STATE_WAIT_SEND_TIMER == appState)
	{
		appState = APP_STATE_SEND;
	}
	else
	{
		SYS_TimerStart(&appDataSendingTimer);
	}

	(void)timer;
}

static void appDataConf(uint8_t msgConfHandle, miwi_status_t status, uint8_t* msgPointer)
{
	/* Your code here... */
}


static void appSendData(void)
{
	/* Your code here... */
}

void appLinkFailureCallback(void)
{
	/* On link failure initiate search to establish connection */
	appState = APP_STATE_CONNECT_NETWORK;
	SYS_TimerStop(&appDataSendingTimer);
}

void searchConfim(uint8_t foundScanResults, void* ScanResults)
{
	searchConf_t* searchConfRes = (searchConf_t *)ScanResults;
	if (foundScanResults)
	{
		for (uint8_t loopindex = 0; loopindex < foundScanResults; loopindex++)
		{
			if (searchConfRes->beaconList[loopindex].connectionPermit)
			{
				MiApp_EstablishConnection(searchConfRes->beaconList[loopindex].logicalChannel,
				SHORT_ADDR_LEN, (uint8_t*)&searchConfRes->beaconList[loopindex].shortAddress, CAPABILITY_INFO, Connection_Confirm);
				return;
			}
		}
		/* Initiate the search again since no connection permit found to join */
		appState = APP_STATE_CONNECT_NETWORK;
	}
	else
	{
		/* Initiate the search again since no beacon */
		appState = APP_STATE_CONNECT_NETWORK;
	}
}

static void Connection_Confirm(miwi_status_t status)
{
	if (SUCCESS == status)
	{
        appState = APP_STATE_SEND;
	}
	else
	{
        appState = APP_STATE_CONNECT_NETWORK;
	}
}

static void appInit(void)
{
	appDataSendingTimer.interval = TRANSMISSION_TIME * 1000;
	appDataSendingTimer.mode = SYS_TIMER_INTERVAL_MODE;
	appDataSendingTimer.handler = appDataSendingTimerHandler;

	MiApp_SubscribeDataIndicationCallback(appDataInd);
	MiApp_SubscribeLinkFailureCallback(appLinkFailureCallback);

	appState = APP_STATE_CONNECT_NETWORK;
}


static void APP_TaskHandler(void)
{
	switch (appState) {
		case APP_STATE_INITIAL:
		{
			appInit();
		}
		break;

		case APP_STATE_CONNECT_NETWORK:
		{
			MiApp_SearchConnection(APP_SCAN_DURATION, CHANNEL_MAP, searchConfim);
			appState = APP_STATE_CONNECTING_NETWORK;
		}
		break;

		case APP_STATE_SEND:
		{
			appSendData();
		}
		break;

		case APP_STATE_SENDING_DONE:
		{
			SYS_TimerStart(&appDataSendingTimer);
			appState = APP_STATE_WAIT_SEND_TIMER;
		}
		break;

		default:
		break;
	}
}

void strlight_init(void)
{
	uint8_t i;
	uint64_t ieeeAddr;
	uint64_t invalidIEEEAddr;

	MiApp_ProtocolInit(&defaultParamsRomOrRam, &defaultParamsRamOnly);
	/* Check if a valid IEEE address is available. */
	memcpy((uint8_t *)&ieeeAddr, (uint8_t *)&myLongAddress, LONG_ADDR_LEN);
	memset((uint8_t *)&invalidIEEEAddr, 0xFF, sizeof(invalidIEEEAddr));
	srand(PHY_RandomReq());
	/*
		* This while loop is on purpose, since just in the
		* rare case that such an address is randomly
		* generated again, we must repeat this.
		*/
	while ((ieeeAddr == 0x0000000000000000) || (ieeeAddr == invalidIEEEAddr))
	{
		/*
			* In case no valid IEEE address is available, a random
			* IEEE address will be generated to be able to run the
			* applications for demonstration purposes.
			* In production code this can be omitted.
			*/
		uint8_t* peui64 = (uint8_t *)&myLongAddress;
		for(i = 0; i<MY_ADDRESS_LENGTH; i++)
		{
			*peui64++ = (uint8_t) rand();
		}
		memcpy((uint8_t *)&ieeeAddr, (uint8_t *)&myLongAddress, LONG_ADDR_LEN);
	}
	PHY_SetIEEEAddr((uint8_t *)&ieeeAddr);
}

void strlight_task(void)
{
	MeshTasks();
	APP_TaskHandler();
}
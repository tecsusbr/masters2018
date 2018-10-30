#ifndef __CONFIGURE_MESH_H
#define __CONFIGURE_MESH_H

   #include "miwi_config.h"

   #if defined(PROTOCOL_MESH)

    /* Channel Map for Network Operation - Configurable */
    #if (defined(PHY_AT86RF212B))
        #define CHANNEL_MAP    (1 << 2)
    /* Range for default configuration: 1 to 10
    Note: TX Power and PHY Mode Setting needs to be modified as per the 
    recommendation from Data Sheet for European band (ie.,Channel 0)*/
    #else
        #define CHANNEL_MAP    (1 << 25)
    /* Range: 11 to 26 */
    #endif

    #ifdef MESH_SECURITY
    /* Security Level Used for transmission of frames..Configurable */
    #define MESH_SECURITY_LEVEL   5
	#endif

    /* Public Key of the Network. It is preinstalled key on all MiWi Mesh Devices  */
    //#define PUBLIC_KEY_DEFAULT  {0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F}
	#define PUBLIC_KEY_DEFAULT  {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F}

    /* Network Key, Key Decided by PAN Coordinator. This is the key used by default  */
    //#define NETWORK_KEY_DEFAULT {0x01, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
	#define NETWORK_KEY_DEFAULT {0x11, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0}

	/* Interval between keep alive message transmission in seconds for coordinator */
	#define KEEP_ALIVE_COORDINATOR_SEND_INTERVAL    120

	/* Keep alive coordinator timeout in seconds */
    #define KEEP_ALIVE_COORDINATOR_TIMEOUT_IN_SEC    KEEP_ALIVE_COORDINATOR_SEND_INTERVAL * 10

	/* Interval between keep alive message transmission in seconds for RxonWhenIdle End device */
	#define KEEP_ALIVE_RXONENDDEVICE_SEND_INTERVAL  120

	/* Keep alive Rx on End device timeout in seconds */
	#define KEEP_ALIVE_RXONENDDEVICE_TIMEOUT_IN_SEC    KEEP_ALIVE_RXONENDDEVICE_SEND_INTERVAL * 10

    /* The Periodic Polling data request interval for sleeping end devices - Configurable  */
    #define DATA_REQUEST_SEND_INTERVAL       3

    /* End Device Key Alive Timeout - Configurable */
    #define RXOFF_DEVICE_TIMEOUT_IN_SEC      DATA_REQUEST_SEND_INTERVAL * 20


	#define MAX_NUMBER_OF_DEVICES_IN_NETWORK     32

    /* Capability of Device Types - Macros - Don't Change */
    #define CAPABILITY_INFO_COORD       0x05
    #define CAPABILITY_INFO_ED          0x06
    #define CAPABILITY_INFO_ED_RXON     0x07

    #define JOINWISH_ENDEVICE           0x01
    #define JOINWISH_COORD_ALONE        0x02
    #define JOINWISH_ANY                0x03


    #ifdef COORDINATOR
       /* JoinWish of Coordinator Device - Configurable */
       #define JOIN_WISH         JOINWISH_ANY
       /* Capability of of Coordinator Device - Don't change */
       #define CAPABILITY_INFO   CAPABILITY_INFO_COORD
    #else
       /* JoinWish and Capability of of End Device - Don't change */
       #define JOIN_WISH         JOINWISH_ENDEVICE
       #define CAPABILITY_INFO  CAPABILITY_INFO_ED
    #endif

	#define ROLE_UPGRADE_INTERVAL_IN_SEC     25
	#define CONNECTION_RESPONSE_WAIT_IN_SEC  5

    /* Maximum number of coordinators in the network - Configurable  */
    #define NUM_OF_COORDINATORS         64
    /* Maximum number of Non Sleep End devices in the network - Configurable  */
    #define NUM_OF_NONSLEEPING_ENDDEVICES        5
    /* Maximum number of Sleeping End devices in the network - Configurable  */
    #define NUM_OF_SLEEPING_ENDDEVICES           5
    /* The Periodic Route Update Initiation interval - Configurable  */
	#define ROUTE_UPDATE_INTERVAL       60
    /* The wait time for receiving route reply after initiating route request - Configurable*/
    #define ROUTE_REQ_WAIT_INTERVAL     5

    /* The wait time to maintain the indirect data in queue - Configurable*/
    #define INDIRECT_DATA_WAIT_INTERVAL 25

    /* The Max number of failures to reach the parent before raising failure callback  - Configurable  */
    #define ED_LINK_FAILURE_ATTEMPTS    15

    /* The time to wait for acknowledgment before next retry of the packet  - Configurable  */
    #define FRAME_ACK_WAIT_INTERVAL     5

    /* The Max number of frame retries in the network layer  - Configurable  */
    #define FRAME_RETRY                 3

    /* Number of Rebroadcast Table Entries  - Configurable  */
    #define REBROADCAST_TABLE_SIZE      10

    /* The time to hold the rebroadcasted entry in the table  - Configurable  */
    #define REBROADCAST_TIMEOUT         5

    /* The number of maximum beacon results to store during scan procedure - Configurable*/
    #define MAX_BEACON_RESULTS          5
  #endif
#endif


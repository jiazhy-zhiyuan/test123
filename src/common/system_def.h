#ifndef __SYSTEM_DEF_ETAH_201304111131_H_
#define __SYSTEM_DEF_ETAH_201304111131_H_
#include "../../include/system.h"

typedef enum VIP_PORT_MODE
{
	VIP_PORT_MODE_BT656,
	VIP_PORT_MODE_BT1120
} VIP_PORT_MODE;

#define     NUM_BUFS_PER_CH_DEC_SD               (6)
#define     NUM_BUFS_PER_CH_DEC_HD               (4)

#define MAX_ENCODE_CHN		16

extern DEVICE_CAPABILITY g_dev;

#endif


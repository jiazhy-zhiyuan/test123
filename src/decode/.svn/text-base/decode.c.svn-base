#include "common.h"

#include "decode.h"
#include "encode.h"
#include "split.h"
#include "../common_sdk.h"
#include "../common/system_def.h"

#include "vdec_vdis.h"

static int decode_show_channel;
static int decode_channel_enable[MAX_VIDEO_DECODE_NUM] = {0 };

int DecodeInit(int channel)
{
	decode_show_channel = g_dev.decode_channel_num;
	decode_channel_enable[channel] = 0;
	return 0;
}

int DecodeUninit(int channel)
{
	return 0;
}

int DecodeStart(int channel)
{
	//Vdec_enableChn(channel);
	decode_show_channel++;
	decode_channel_enable[channel] = 1;
	return 0;
}

int DecodeStop(int channel)
{
	//Vdec_disableChn(channel);
	decode_show_channel--;
	decode_channel_enable[channel] = 0;
	return 0;
}

int decode_static[32] = {0 };
int DecodePutBuffer(int channel, void *pBuffer, int dwCount)
{
	VCODEC_BITSBUF_LIST_S emptyBufList;
	if(0 == decode_channel_enable[channel])
		return -1;

	OSA_waitMsecs(MCFW_IPCBITS_SENDFXN_PERIOD_MS);
	g_debug_info.video_decode_cnt[channel]++;
	g_debug_info.video_decode_size[channel] += dwCount;
	decode_static[channel]++;
	VdecVdis_bitsRdGetEmptyBitBufs(&emptyBufList,channel);
	VdecVdis_bitsRdReadData(&emptyBufList,channel,pBuffer,dwCount);
	VdecVdis_bitsRdSendFullBitBufs(&emptyBufList);

	return 0;
}


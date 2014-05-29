/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/


#include "common.h"

#include "decode.h"
#include "encode.h"
#include "split.h"
#include "../common_sdk.h"

#include "encode_def.h"
#include "vcap_venc_vdis.h"


#define FILE_WRITE_STOPPED  (0)
#define FILE_WRITE_RUNNING  (1)

VcapVenc_Ctrl gVcapVenc_ctrl;
extern EncodeGetBuffer_Callback g_EncodeGetCallback;

Int32 VcapVenc_resetStatistics()
{
	UInt32 chId;
	VcapVenc_ChInfo *pChInfo;

	for(chId=0; chId<VENC_CHN_MAX; chId++)
	{
		pChInfo = &gVcapVenc_ctrl.chInfo[chId];

		pChInfo->totalDataSize = 0;
		pChInfo->numKeyFrames = 0;
		pChInfo->numFrames = 0;
		pChInfo->maxWidth = 0;
		pChInfo->minWidth = 0xFFF;
		pChInfo->maxHeight= 0;
		pChInfo->minHeight= 0xFFF;
		pChInfo->maxLatency= 0;
		pChInfo->minLatency= 0xFFF;

	}

	gVcapVenc_ctrl.statsStartTime = OSA_getCurTimeInMsec();

	return 0;
}

Int32 VcapVenc_printStatistics(Bool resetStats)
{
	UInt32 chId;
	VcapVenc_ChInfo *pChInfo;
	float elaspedTime;

	elaspedTime = OSA_getCurTimeInMsec() - gVcapVenc_ctrl.statsStartTime;

	elaspedTime /= 1000.0; // in secs

	printf( "\n"
			"\n *** Encode Bitstream Received Statistics *** "
			"\n"
			"\n Elased time = %6.1f secs"
			"\n"
			"\n CH | Bitrate (Kbps) | FPS | Key-frame FPS | Width (max/min) | Height (max/min) | Latency (max/min)"
			"\n --------------------------------------------------------------------------------------------------",
			elaspedTime
	      );

	for(chId=0; chId<VENC_CHN_MAX;chId++)
	{
		pChInfo = &gVcapVenc_ctrl.chInfo[chId];

		if(pChInfo->numFrames)
		{
			printf("\n %2d | %14.2f | %3.1f | %13.1f | %5d / %6d | %6d / %6d  | %6d / %6d",
					chId,
					(pChInfo->totalDataSize*8.0/elaspedTime)/1024.0,
					pChInfo->numFrames*1.0/elaspedTime,
					pChInfo->numKeyFrames*1.0/elaspedTime,
					pChInfo->maxWidth,
					pChInfo->minWidth,
					pChInfo->maxHeight,
					pChInfo->minHeight,
					pChInfo->maxLatency,
					pChInfo->minLatency

			      );
		}
	}

	printf("\n");

	if(resetStats)
		VcapVenc_resetStatistics();

	return 0;
}

static Void VcapVenc_bitsWriteCbFxn(Ptr pPrm)
{
	OSA_semSignal(&gVcapVenc_ctrl.wrSem);
}

extern int __Encode2ChannelID(int encode_channel);
extern int __Encode2ChannelStream(int encode_channel);

//int encode_static[32] = {0 };
extern int		encode_channel_state[];
void *VcapVenc_bitsWriteMain(void *pPrm)
{
	prctl(15, "vcapvenc_sys");
	Int32 status, frameId;
	VCODEC_BITSBUF_LIST_S bitsBuf;
	VCODEC_BITSBUF_S *pBuf;
	VcapVenc_ChInfo *pChInfo;
	UInt32 latency;

	while(!gVcapVenc_ctrl.exitWrThr) {
		status = OSA_semWait(&gVcapVenc_ctrl.wrSem, OSA_TIMEOUT_FOREVER);
		if(status!=OSA_SOK)
			break;

		status = Venc_getBitstreamBuffer(&bitsBuf, TIMEOUT_NO_WAIT);
		if(status==ERROR_NONE && bitsBuf.numBufs) {
			for(frameId=0; frameId<bitsBuf.numBufs; frameId++) {
				pBuf = &bitsBuf.bitsBuf[frameId];
#if 1
				if(1 == encode_channel_state[pBuf->chnId] && 0 != g_EncodeGetCallback && NULL != pBuf) {
					/*
					printf("A8: channel: %d, write size: %d-------%d,%d\n"
						, pBuf->chnId
						, pBuf->filledBufSize
						, __Encode2ChannelID(pBuf->chnId)
						, __Encode2ChannelStream(pBuf->chnId)
						);
					*/
					int total = g_dev.vi_channel_num + g_dev.swms_encode_num;
                    //printf("<%d - %d>\n", pBuf->frameWidth, pBuf->frameHeight);
					VIDEO_STREAM_PARAM video_stream_param;
					video_stream_param.chnId		= __Encode2ChannelID(pBuf->chnId);
					video_stream_param.stream_type		= __Encode2ChannelStream(pBuf->chnId);
					video_stream_param.encode_type		= 0;
					video_stream_param.frame_type		= pBuf->frameType;
					video_stream_param.bufVirtAddr		= pBuf->bufVirtAddr;
					video_stream_param.filledBufSize	= pBuf->filledBufSize;
					video_stream_param.width		= pBuf->frameWidth;
					video_stream_param.height		= pBuf->frameHeight;
					video_stream_param.timestamp		= pBuf->timestamp;
					video_stream_param.seqId		= pBuf->seqId;
					//encode_static[video_stream_param.chnId]++;

                    
					(g_debug_info.video_encode_cnt[video_stream_param.chnId][video_stream_param.stream_type])++;
					(g_debug_info.video_encode_size[video_stream_param.chnId][video_stream_param.stream_type]) += pBuf->filledBufSize;

					g_EncodeGetCallback(&video_stream_param);
				}
#else
				printf("A8: channel: %d, write size: %d\n", pBuf->chnId, pBuf->filledBufSize);
#endif
				if(pBuf->chnId<VENC_CHN_MAX) {
					pChInfo = &gVcapVenc_ctrl.chInfo[pBuf->chnId];

					pChInfo->totalDataSize += pBuf->filledBufSize;
					pChInfo->numFrames++;
					if(pBuf->frameType==VCODEC_FRAME_TYPE_I_FRAME) {
						pChInfo->numKeyFrames++;
					}

					latency = pBuf->encodeTimestamp - pBuf->timestamp;

					if(latency > pChInfo->maxLatency)
						pChInfo->maxLatency = latency;

					if(latency < pChInfo->minLatency)
						pChInfo->minLatency = latency;

					if(pBuf->frameWidth > pChInfo->maxWidth)
						pChInfo->maxWidth = pBuf->frameWidth;

					if(pBuf->frameWidth < pChInfo->minWidth)
						pChInfo->minWidth = pBuf->frameWidth;

					if(pBuf->frameHeight > pChInfo->maxHeight)
						pChInfo->maxHeight = pBuf->frameHeight;

					if(pBuf->frameHeight < pChInfo->minHeight)
						pChInfo->minHeight = pBuf->frameHeight;

				}

			}

			Venc_releaseBitstreamBuffer(&bitsBuf);
		}
	}

	gVcapVenc_ctrl.isWrThrStopDone = TRUE;

	return NULL;
}

Int32 VcapVenc_bitsWriteCreate()
{
	VENC_CALLBACK_S callback;
	Int32 status;

	gVcapVenc_ctrl.exitWrThr = FALSE;
	gVcapVenc_ctrl.isWrThrStopDone = FALSE;

	callback.newDataAvailableCb = VcapVenc_bitsWriteCbFxn;

	/* Register call back with encoder */
	Venc_registerCallback(&callback,
			(Ptr)&gVcapVenc_ctrl);

	status = OSA_semCreate(&gVcapVenc_ctrl.wrSem, 1, 0);
	OSA_assert(status==OSA_SOK);

	status = OSA_thrCreate(
			&gVcapVenc_ctrl.wrThrHndl,
			VcapVenc_bitsWriteMain,
			OSA_THR_PRI_DEFAULT,
			0,
			&gVcapVenc_ctrl
			);

	OSA_assert(status==OSA_SOK);

	return OSA_SOK;
}

Int32 VcapVenc_bitsWriteDelete()
{
	gVcapVenc_ctrl.exitWrThr = TRUE;
	OSA_semSignal(&gVcapVenc_ctrl.wrSem);

	while(!gVcapVenc_ctrl.isWrThrStopDone)
	{
		OSA_waitMsecs(10);
	}

	OSA_thrDelete(&gVcapVenc_ctrl.wrThrHndl);
	OSA_semDelete(&gVcapVenc_ctrl.wrSem);

	return OSA_SOK;
}



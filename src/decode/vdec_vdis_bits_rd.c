/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/

/**
  \file demo_vdec_vdis_bits_rd.c
  \brief
  */
	  
#include "../common_sdk.h"
#include "vdec_vdis.h"

VdecVdis_IpcBitsCtrl gVdecVdis_obj;
VdecVdis_Config      gVdecVdis_config;

#if 0
#else
Void VdecVdis_bitsRdGetEmptyBitBufs(VCODEC_BITSBUF_LIST_S *emptyBufList, Int32 chId)
{
    VDEC_BUF_REQUEST_S reqInfo;

    emptyBufList->numBufs = 0;

    reqInfo.chNum = chId;
    reqInfo.bufSize = gVdecVdis_config.chBufSize[chId];
    //printf("reqInfo.bufSize: %d, chId: %d\n", reqInfo.bufSize, chId);

    Vdec_requestBitstreamBuffer(&reqInfo, emptyBufList, 0);
}
#endif


#define VDEC_VDIS_FRAME_DURATION_MS (33)
#if 1
static Void VdecVdis_setFrameTimeStamp(VCODEC_BITSBUF_S *pEmptyBuf)
{
    UInt64 curTimeStamp =
      gVdecVdis_config.frameCnt[pEmptyBuf->chnId] * VDEC_VDIS_FRAME_DURATION_MS;
    pEmptyBuf->lowerTimeStamp = (UInt32)(curTimeStamp & 0xFFFFFFFF);
    pEmptyBuf->upperTimeStamp = (UInt32)((curTimeStamp >> 32)& 0xFFFFFFFF);
    if (0 == gVdecVdis_config.frameCnt[pEmptyBuf->chnId])
    {
        UInt32 displayChId;

        Vdec_mapDec2DisplayChId(VDIS_DEV_HDMI,pEmptyBuf->chnId,&displayChId);
        Vdis_setFirstVidPTS(VDIS_DEV_HDMI,displayChId,curTimeStamp);
        Vdec_mapDec2DisplayChId(VDIS_DEV_HDCOMP,pEmptyBuf->chnId,&displayChId);
        Vdis_setFirstVidPTS(VDIS_DEV_HDCOMP,displayChId,curTimeStamp);
        Vdec_mapDec2DisplayChId(VDIS_DEV_SD,pEmptyBuf->chnId,&displayChId);
        Vdis_setFirstVidPTS(VDIS_DEV_SD,displayChId,curTimeStamp);
    }
    gVdecVdis_config.frameCnt[pEmptyBuf->chnId] += 1;
}
#endif

Void VdecVdis_bitsRdReadData(VCODEC_BITSBUF_LIST_S  *emptyBufList,UInt32 resId, void *pBuffer, int dwCount)
{
    VCODEC_BITSBUF_S *pEmptyBuf;
    Int i;

    for (i = 0; i < emptyBufList->numBufs; i++)
    {
        pEmptyBuf = &emptyBufList->bitsBuf[i];
        //VdecVdis_bitsRdFillEmptyBuf(pEmptyBuf);
        pEmptyBuf->filledBufSize = dwCount;
	memcpy(pEmptyBuf->bufVirtAddr, pBuffer, dwCount);

	VdecVdis_setFrameTimeStamp(pEmptyBuf);
    }
}

Void VdecVdis_bitsRdSendFullBitBufs( VCODEC_BITSBUF_LIST_S *fullBufList)
{
    if (fullBufList->numBufs)
    {
        Vdec_putBitstreamBuffer(fullBufList);
    }
}

static Void *VdecVdis_bitsRdSendFxn(Void * prm)
{
    return NULL;
}

Void VdecVdis_bitsRdInitThrObj()
{
    int status;

    gVdecVdis_obj.thrExit = FALSE;
    status = OSA_semCreate(&gVdecVdis_obj.thrStartSem,1,0);
    OSA_assert(status==OSA_SOK);

    status = OSA_thrCreate(&gVdecVdis_obj.thrHandle,
            VdecVdis_bitsRdSendFxn,
            MCFW_IPCBITS_SENDFXN_TSK_PRI,
            MCFW_IPCBITS_SENDFXN_TSK_STACK_SIZE,
            &gVdecVdis_obj);

    OSA_assert(status==OSA_SOK);
}

Void VdecVdis_bitsRdDeInitThrObj()
{
    gVdecVdis_obj.thrExit = TRUE;
    OSA_thrDelete(&gVdecVdis_obj.thrHandle);
    OSA_semDelete(&gVdecVdis_obj.thrStartSem);
}



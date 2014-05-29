/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/



#ifndef _VCAP_VENC_VDIS_H_
#define _VCAP_VENC_VDIS_H_
#include "common.h"

#include "decode.h"
#include "encode.h"
#include "split.h"

#include <sys/mman.h>

//#define CUSTOM_SD_DEMO
//#define IPC_BITS_DEBUG

#define MMAP_MEM_PAGEALIGN         (4*1024-1)

typedef struct {

	UInt32 totalDataSize;
	UInt32 numKeyFrames;
	UInt32 numFrames;
	UInt32 maxWidth;
	UInt32 minWidth;
	UInt32 maxHeight;
	UInt32 minHeight;
	UInt32 maxLatency;
	UInt32 minLatency;

} VcapVenc_ChInfo;

typedef struct VcapVenc_IpcFramesCtrlThrObj {
	OSA_ThrHndl thrHandleFramesInOut;
	OSA_SemHndl framesInNotifySem;
	volatile Bool exitFramesInOutThread;
} VcapVenc_IpcFramesCtrlThrObj;

typedef struct VcapVenc_IpcFramesCtrl {
	Bool  noNotifyFramesInHLOS;
	Bool  noNotifyFramesOutHLOS;
	VcapVenc_IpcFramesCtrlThrObj  thrObj;
} VcapVenc_IpcFramesCtrl;

typedef struct {

	OSA_ThrHndl wrThrHndl;
	OSA_SemHndl wrSem;
	Bool exitWrThr;
	Bool isWrThrStopDone;

	VcapVenc_ChInfo chInfo[VENC_CHN_MAX];

	UInt32 statsStartTime;
	VcapVenc_IpcFramesCtrl ipcFrames;
} VcapVenc_Ctrl;

#ifdef CUSTOM_SD_DEMO
typedef struct
{
	unsigned int memAddr;
	unsigned int memSize;
	unsigned int mmapMemAddr;
	unsigned int mmapMemSize;  
	unsigned int memOffset;

	int    memDevFd;
	volatile unsigned int *pMemVirtAddr;

} VcapVenc_mMapCtrl;
#endif

extern VcapVenc_Ctrl gVcapVenc_ctrl;

Int32 VcapVenc_resetStatistics();
Int32 VcapVenc_printStatistics(Bool resetStats);

Int32 VcapVenc_bitsWriteCreate();
Int32 VcapVenc_bitsWriteDelete();

Int32 VcapVenc_ipcFramesCreate(int demoId);
Int32 VcapVenc_ipcFramesDelete();
Void  VcapVenc_ipcFramesStop(void);
Void  VcapVenc_ipcFramesInSetCbInfo (void);

#ifdef CUSTOM_SD_DEMO
Void  VcapVenc_ipcFramesFileWriteCreate();
Void  VcapVenc_ipcFramesFileOpen();
Void  VcapVenc_ipcFrameFileWrite(VIDEO_FRAMEBUF_LIST_S * pFrameBufList);

Int32 VcapVenc_mMap(UInt32 physAddr, Uint32 memSize , UInt32 * pMemVirtAddr);
Int32 VcapVenc_unmapMem();
#endif

#endif

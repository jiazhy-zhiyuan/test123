/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/



#ifndef _DEMO_H_
#define _DEMO_H_

#include <osa.h>
#include <osa_thr.h>
#include <osa_sem.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

#include "ti_vdis_common_def.h"
#include "ti_vdec_common_def.h"

#include "ti_vsys.h"
#include "ti_vcap.h"
#include "ti_venc.h"
#include "ti_vdec.h"
#include "ti_vdis.h"
#include "ti_vdis_timings.h"
#include "ti_audio.h"

#include "demos/graphic/graphic.h"

#include <demos/mcfw_api_demos/mcfw_demo/demo_swms.h>


/* To select if FBDEV interface is used for Graphics */
#if defined(TI_814X_BUILD)
#define USE_FBDEV   0
#endif

#if defined(TI_8107_BUILD)
#define USE_FBDEV   0
#endif

#if defined(TI_816X_BUILD)
#define USE_FBDEV   0
#endif

#define DEMO_VCAP_VENC_VDEC_VDIS_PROGRESSIVE            (0)
#define DEMO_VCAP_VENC_VDEC_VDIS_INTERLACED             (1)
#define DEMO_VCAP_VENC_VDIS                             (2)
#define DEMO_VCAP_VENC_VDIS_HD                          (3)
#define DEMO_VDEC_VDIS                                  (4)
#define DEMO_VCAP_VDIS                                  (5)
#define DEMO_VCAP_VENC_VDEC_VDIS_PROGRESSIVE_NON_D1     (6)
#define DEMO_VCAP_VENC_VDEC_VDIS_PROGRESSIVE_4CH        (7)
#define DEMO_VCAP_VENC_VDEC_VDIS_PROGRESSIVE_8CH        (8)
#define DEMO_VCAP_VENC_VDEC_VDIS_PROGRESSIVE_16CH_NRT   (9)
#define DEMO_VCAP_VENC_VDEC_VDIS_PROGRESSIVE_8CH_NRT    (10)
#define DEMO_HYBRIDDVR_16CH                             (11)
#define DEMO_CARDVR_4CH                                 (12)
#define DEMO_HYBRIDENC_36CH                             (13)
#define DEMO_HD_SD_5CH                                  (14)
#define DEMO_VCAP_VENC_VDIS_HD_SD                       (15)
#define DEMO_LAST                                       (DEMO_VCAP_VENC_VDIS_HD_SD+1)
#define DEMO_MAX                                        (DEMO_LAST)


#define DEMO_HD_DISPLAY_DEFAULT_STD             (VSYS_STD_1080P_60)

#define MAX_INPUT_STR_SIZE                      (128)
#define DEMO_SW_MS_INVALID_ID                   (0xFF)


#define SCD_MAX_TILES                           (9)
#define SCD_MAX_CHANNELS                        (16)


/* The below part is temporary for OSD specific items */
#define DEMO_OSD_NUM_WINDOWS        (4)
#define DEMO_OSD_NUM_BLIND_WINDOWS  (4)
#define DEMO_OSD_WIN_MAX_WIDTH   (320)
#define DEMO_OSD_WIN_MAX_HEIGHT  (64)
#define DEMO_OSD_WIN_WIDTH       (224)
#define DEMO_OSD_WIN_HEIGHT      (30)
#define DEMO_OSD_WIN0_STARTX     (16)
#define DEMO_OSD_WIN0_STARTY     (16)

#define DEMO_OSD_WIN_PITCH_H     (224)
#define DEMO_OSD_WIN_PITCH_V     (30)
#define DEMO_OSD_TRANSPARENCY    (1)
#define DEMO_OSD_GLOBAL_ALPHA    (0x80)
#define DEMO_OSD_ENABLE_WIN      (1)

#define DEMO_ENC_NUM_RESOLUTION_STREAMS     (4)
#define DEMO_BLIND_AREA_NUM_WINDOWS     (4)
#define DEMO_BLIND_AREA_WIN_WIDTH       (50)
#define DEMO_BLIND_AREA_WIN_HEIGHT      (20)
#define DEMO_BLIND_AREA_WIN0_STARTX     (512)
#define DEMO_BLIND_AREA_WIN0_STARTY     (16)
#define DEMO_SCD_ENABLE_MOTION_TRACKING (1)
#define DEMO_SCD_ENABLE_FILE_WRITE      (0)

/** @enum Demo_SCDResolutionClass
 *  @brief Enumeration of different resolution class.
 */
typedef enum Demo_SCDResolutionClass {
    DEMO_SCD_RESOLUTION_CLASS_FIRST = 0,
    DEMO_SCD_RESOLUTION_CLASS_CIF  = DEMO_SCD_RESOLUTION_CLASS_FIRST,
    /* 176x120 or 176x144 */
    DEMO_SCD_RESOLUTION_CLASS_QCIF,
    /* 352x240 or 352x288 */
    DEMO_SCD_RESOLUTION_CLASS_LAST  = DEMO_SCD_RESOLUTION_CLASS_QCIF,
    DEMO_SCD_RESOLUTION_CLASS_COUNT = (DEMO_SCD_RESOLUTION_CLASS_LAST + 1)
} Demo_SCDResolutionClass;

typedef enum {
    DEMO_TYPE_PROGRESSIVE,
    DEMO_TYPE_INTERLACED
}demoType;

typedef enum {
    DEMO_AUDIO_TYPE_NONE,
    DEMO_AUDIO_TYPE_CAPTURE,
    DEMO_AUDIO_TYPE_ENCODE,
    DEMO_AUDIO_TYPE_DECODE,
    DEMO_AUDIO_TYPE_CHANGE_PLAYBACK_CHANNEL /* valid only if capture + playback demo is active */
} demoAudioType;

typedef struct {

    UInt32 maxVencChannels;
    UInt32 maxVcapChannels;
    UInt32 maxVdisChannels;
    UInt32 maxVdecChannels;
    UInt32 VsysNumChs;

    Bool   audioCaptureActive;
    Bool   audioPlaybackActive;
    Int8   audioCaptureChNum;
    Int8   audioPlaybackChNum;
    Bool   osdEnable;
    Bool   scdTileConfigInitFlag;
    demoType Type;
    demoAudioType audioType;
    Bool          audioInitialized;
    VSYS_USECASES_E usecase;
    UInt32 numDeis;
    UInt32 numSwMs;
    UInt32 numDisplays;
    UInt32 numEncChannels[DEMO_ENC_NUM_RESOLUTION_STREAMS];
    UInt32 bitRateKbps[DEMO_ENC_NUM_RESOLUTION_STREAMS];
    UInt32 defaultLayoutId[VDIS_DEV_MAX];
    UInt32 defaultLayoutStartCh[VDIS_DEV_MAX];
    UInt32 numTiedVencs;
    UInt32 tiedVencIds[VDIS_DEV_MAX];
    Bool   scdEnable;
    UInt32 curDisplaySeqId;

} Demo_Info;
typedef struct {
    UInt32 chId;
    UInt32 maxWidth;
    UInt32 maxHeight;
    UInt32 videoMode; /* 0 == PAL, 1 = NTSC */
    AlgLink_ScdChParams scdChPrm;
    UInt32 numHorzBlks;
    UInt32 numVertBlks;
    UInt32 numBlksInFrame;
    UInt32 blkHeight;
} Demo_ScdChInfo;

typedef struct {
    UInt32 numCh;
    UInt32 numVaCh;
    char   iniPath[MAX_INPUT_STR_SIZE];
    Demo_ScdChInfo chInfo[VENC_CHN_MAX];
} Demo_ScdInfo;


typedef struct {

    Int8  inFile[MAX_INPUT_STR_SIZE];
    Int8  outFile[MAX_INPUT_STR_SIZE];
    Int32 bitRate;
    Int32 numChannels;
    Int32 sampleRate;
    Int32 encodeType;
} Audio_EncInfo;

typedef struct {

    Int8  inFile[MAX_INPUT_STR_SIZE];
    Int8  outFile[MAX_INPUT_STR_SIZE];
    Int32 numChannels;
    Int32 decodeType;

} Audio_DecInfo;

typedef struct {

    Int8  outFilePath[MAX_INPUT_STR_SIZE];
    Int32 numEncodeChannels;
    Int8  enablePlayback;
    UInt8 playbackChNum;
    Int8  playbackEncodedFlag;
    Int8  playbackDevId;
} Audio_CapInfo;

extern Demo_Info gDemo_info;
extern AlgLink_OsdChWinParams g_osdChParam[];
extern AlgLink_OsdChBlindWinParams g_osdChBlindParam[];
extern CaptureLink_BlindInfo g_blindAreaChParam[];

Void  VcapVdis_start();
Void  VcapVdis_stop();

Void  VcapVenc_start(Bool hdDemo);
Void  VcapVenc_stop();
Int32 VcapVenc_printStatistics(Bool resetStats);
Int32 Scd_printStatistics(Bool resetStats);


Void  VdecVdis_start();
Void  VdecVdis_stop();

Void  VcapVencVdecVdis_start( Bool doProgressiveVenc, Bool enableSecondaryOut, int demoId );
Void  VcapVencVdecVdis_stop();
Int32 VcapVencVdecVdis_printStatistics(Bool resetStats, Bool allChs);

void  Demo_generateH264HdrFile(char *filename);
void  Demo_generateMjpgHdrFile(char *filename);
void  Demo_generateMpeg4HdrFile(char *filename);
void  Demo_generateMpeg2HdrFile(char *filename);

Int32 Demo_swMsGetOutSize(UInt32 outRes, UInt32 * width, UInt32 * height);

int Demo_audioCaptureStop();
int Demo_audioCaptureSetParams(Bool set_params);
int Demo_audioSetParams();
int Demo_audioPlaybackStop();
int Demo_audioCaptureStart(UInt32 chId);
int Demo_audioPlaybackStart(UInt32 chId, UInt32 playbackDevId);
int Demo_audioSettings(int demoId);

int Demo_captureSettings(int demoId);
int Demo_captureGetVideoSourceStatus();
int Demo_captureGetTamperStatus(Ptr pPrm);
int Demo_captureGetMotionStatus(Ptr pPrm);
int Demo_decodeErrorStatus(Ptr pPrm);

int Demo_decodeWatermarkCheckFail(Ptr pPrm);
VSYS_VIDEO_STANDARD_E Demo_captureGetSignalStandard();

int Demo_encodeSettings(int demoId);

int Demo_decodeSettings(int demoId);

int Demo_displaySwitchChn(int devId, int startChId);
int Demo_displaySwitchSDChan(int devId, int startChId);
int Demo_displayChnEnable(int chId, Bool enable);
int Demo_displayGetLayoutId(int demoId);
int Demo_displaySetResolution(UInt32 displayId, UInt32 resolution);
int Demo_displaySettings(int demoId);
UInt32 Demo_displayGetCurSeqId();
Int32 Demo_displayGetChTimeInfo (Int32 chNum, Bool *displayStarted, UInt64 *firstPTS, UInt64 *currPTS);

Int32 Demo_osdInit(UInt32 numCh, UInt16 *osdFormat);
Void  Demo_osdDeinit();

Int32 Demo_scdInit(UInt32 numCh, UInt32 startChId, UInt32 scdResolution, UInt32 videoMode, UInt32 demoId);
Int32 Demo_scdUpdateParam(UInt32 chId, UInt32 width, UInt32 height);
Int32 Demo_scdUpdateBlkConfigParam(UInt32 chId, UInt32 demoId);
Void Demo_scdVaParamInit(UInt32 demoId);
Void Demo_scdUpdateVaParam();

Int32 Demo_blindAreaInit(UInt32 numCh, UInt32 demoId);

int  Demo_printInfo(int demoId);
Int32 Demo_startStopAudioEncodeDecode (Int32 demoId, Int32 option, Bool userOpt);
int Demo_printBuffersInfo();
int Demo_printAvsyncInfo();
int Demo_switchIVAMap();
int  Demo_startStop(int demoId, Bool startDemo);
int  Demo_run(int demoId);
char Demo_getChar();
int  Demo_getChId(char *string, int maxChId);
int  Demo_getIntValue(char *string, int minVal, int maxVal, int defaultVal);
Bool Demo_getFileWriteEnable();
Bool Demo_getMotionTrackEnable();
Bool Demo_isPathValid( const char* absolutePath );
Bool Demo_isFileValid( const char* absolutePath );
int  Demo_getFileWritePath(char *path, char *defaultPath);
Void VdecVdis_setTplayConfig(VDIS_CHN vdispChnId, VDIS_AVSYNC speed);

#if defined(TI_814X_BUILD) || defined(TI_8107_BUILD)
int Demo_change8ChMode(int demoId);
int Demo_change16ChMode(int demoId);
#endif

Void Demo_initAudioSystem(Void);
Void Demo_deInitAudioSystem(Void);

Bool Demo_startAudioEncodeSystem (Void);
Bool Demo_startAudioDecodeSystem (Void);
Bool Demo_startAudioCaptureSystem (Void);
Bool Demo_signalCaptureThread (void);
Bool Demo_changePlaybackChannel (Void);
Bool Demo_stopAudioDecodeSystem(Bool userOpt);
Bool Demo_stopAudioEncodeSystem (Bool userOpt);
Bool Demo_stopAudioCaptureSystem (Bool userOpt);
Bool Demo_IsCaptureActive(Void);
Bool Demo_IsEncodeActive(Void);
Bool Demo_IsDecodeActive(Void);
Bool Demo_isSinkDetected(void);
Int32 Demo_getSinkDetails(VDIS_SCREEN_INFO_S **pSInfo);
int __EncodeShowTime(int ichannel, int bShowTime);

#endif /* TI_MULTICH_DEMO_H */

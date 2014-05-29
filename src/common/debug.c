#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "decode.h"
#include "encode.h"
#include "split.h"
#include "../common_sdk.h"

int Demo_captureGetCaptureChNum (int scdChNum);
int Demo_captureGetCaptureChNum (int scdChNum);
int __SpitSetCompositorCommon(UInt32 displayId, UInt32 resolution);
Int32 Demo_CCSCrashDumpFormatSave(VSYS_SLAVE_CORE_EXCEPTION_INFO_S *excInfo,FILE *fp);


#define __PRINTK_BIN_LINE_SIZE		32	/* 每行打印的字符数量 */

int printfbin(void *buf_, int size)
{
	unsigned char *buf = (unsigned char *)buf_;
	unsigned char tmp;
	int i, j;

	for (i = 0; i < size; i+=__PRINTK_BIN_LINE_SIZE) {
		printf("%08x:", (unsigned int)(buf + i));
		for(j = i; j < i+ __PRINTK_BIN_LINE_SIZE; j++) {
			if(0 == (j -i) % (__PRINTK_BIN_LINE_SIZE / 2))
				printf(" ");
			printf("%02x ", *(buf + j));
		}
		printf("|");
		for(j = i; j < i+ __PRINTK_BIN_LINE_SIZE; j++) {
			tmp = *(buf + j);
			printf("%c", isprint(tmp)? tmp: '.');
		}
		printf("|\n");;
	}

	return 0;
}

char gDemo_decodeSettingsMenu[] = {
	"\r\n ===================="
		"\r\n Decode Settings Menu"
		"\r\n ===================="
		"\r\n"
		"\r\n 1: Disable channel"
		"\r\n 2: Enable  channel"
		"\r\n 3: Create channel"
		"\r\n 4: Delete channel"
		"\r\n 5: Switch File - Works only for Decode->Display usecase"
		"\r\n 6: Enable/Disable Decoder Error Reporting"
		"\r\n b: Get decoder buffer stats"
		"\r\n"
		"\r\n p: Previous Menu"
		"\r\n"
		"\r\n Enter Choice: "
};

/**
 *******************************************************************************
 *  @struct sEnumToStringMapping
 *  @brief  Error Name Mapping to give error message.
 *          This structure contains error reporting strings which are mapped to
 *          Codec errors
 *
 *  @param  errorName : Pointer to the error string
 * 
 *******************************************************************************
 */
typedef struct _sEnumToStringMapping
{
	char *errorName;
}sEnumToStringMapping;

/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to codec errors                             */
/* Please refer User guide for more details on error strings                  */
/*----------------------------------------------------------------------------*/
static sEnumToStringMapping gDecoderErrorStrings[32] = 
{
	{(char *)"IH264VDEC_ERR_NOSLICE : 0, \0"},
	{(char *)"IH264VDEC_ERR_SPS : 1,"},
	{(char *)"IH264VDEC_ERR_PPS : 2,\0"},
	{(char *)"IH264VDEC_ERR_SLICEHDR : 3,\0"},
	{(char *)"IH264VDEC_ERR_MBDATA : 4,\0"},
	{(char *)"IH264VDEC_ERR_UNAVAILABLESPS : 5,\0"},
	{(char *)"IH264VDEC_ERR_UNAVAILABLEPPS  : 6,\0"},
	{(char *)"IH264VDEC_ERR_INVALIDPARAM_IGNORE : 7\0"},
	{(char *)"XDM_PARAMSCHANGE : 8,\0"},
	{(char *)"XDM_APPLIEDCONCEALMENT : 9,\0"},
	{(char *)"XDM_INSUFFICIENTDATA : 10,\0"},
	{(char *)"XDM_CORRUPTEDDATA : 11,\0"},
	{(char *)"XDM_CORRUPTEDHEADER : 12,\0"},
	{(char *)"XDM_UNSUPPORTEDINPUT : 13,\0"},
	{(char *)"XDM_UNSUPPORTEDPARAM : 14,\0"},
	{(char *)"XDM_FATALERROR : 15\0"},
	{(char *)"IH264VDEC_ERR_UNSUPPFEATURE : 16,\0"},
	{(char *)"IH264VDEC_ERR_METADATA_BUFOVERFLOW : 17,\0"},
	{(char *)"IH264VDEC_ERR_STREAM_END : 18,\0"},
	{(char *)"IH264VDEC_ERR_NO_FREEBUF : 19,\0"},
	{(char *)"IH264VDEC_ERR_PICSIZECHANGE : 20,\0"},
	{(char *)"IH264VDEC_ERR_UNSUPPRESOLUTION : 21,\0"},
	{(char *)"IH264VDEC_ERR_NUMREF_FRAMES : 22,\0"},
	{(char *)"IH264VDEC_ERR_INVALID_MBOX_MESSAGE : 23,\0"},
	{(char *)"IH264VDEC_ERR_DATA_SYNC : 24,\0"},
	{(char *)"IH264VDEC_ERR_MISSINGSLICE : 25,\0"},
	{(char *)"IH264VDEC_ERR_INPUT_DATASYNC_PARAMS : 26,\0"},
	{(char *)"IH264VDEC_ERR_HDVICP2_IMPROPER_STATE : 27,\0"},
	{(char *)"IH264VDEC_ERR_TEMPORAL_DIRECT_MODE : 28,\0"},
	{(char *)"IH264VDEC_ERR_DISPLAYWIDTH : 29,\0"},
	{(char *)"IH264VDEC_ERR_NOHEADER : 30,\0"},
	{(char *)"IH264VDEC_ERR_GAPSINFRAMENUM : 31, \0"}
};

/* Global Variables */
/* Flag to indicate / keep track, of TV / Monitor connection / removal */
Bool gIsSinkDetected = FALSE;
/* Variable that holds capabilites of the connected TV / Monitor */
VDIS_SCREEN_INFO_S gScrInfo;

#define DEMO_ENC_NUM_RESOLUTION_STREAMS     (4)

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

Demo_Info gDemo_info = 
{
	.curDisplaySeqId = VDIS_DISPLAY_SEQID_DEFAULT,
};

#define DEMO_LAYOUT_MODE_4CH_4CH    0
#define DEMO_LAYOUT_MODE_4CH        1
#define DEMO_LAYOUT_MODE_1CH        2
#define DEMO_LAYOUT_MODE_9CH        3
#define DEMO_LAYOUT_MODE_6CH        4
#define DEMO_LAYOUT_MODE_16CH       5
#define DEMO_LAYOUT_MODE_7CH_1CH    6
#define DEMO_LAYOUT_MODE_2CH_PIP    7
#define DEMO_LAYOUT_MODE_20CH_4X5   8
#define DEMO_LAYOUT_MODE_25CH_5X5   9
#define DEMO_LAYOUT_MODE_30CH_5X6   10
#define DEMO_LAYOUT_MODE_36CH_6X6   11
#define DEMO_LAYOUT_MAX             12

//static int layoutId = DEMO_LAYOUT_MODE_7CH_1CH; // Have this static to use layoutId in Demo_displayChangeFpsForLayout() when channel remap alone happens

int Demo_captureGetVideoSourceStatus()
{
	UInt32 chId;

	VCAP_VIDEO_SOURCE_STATUS_S videoSourceStatus;
	VCAP_VIDEO_SOURCE_CH_STATUS_S *pChStatus;

	Vcap_getVideoSourceStatus( &videoSourceStatus );

	printf(" \n");

	for(chId=0; chId<videoSourceStatus.numChannels; chId++)
	{
		pChStatus = &videoSourceStatus.chStatus[chId];

		if(pChStatus->isVideoDetect)
		{
			printf (" DEMO: %2d: Detected video at CH [%d,%d] (%dx%d@%dHz, %d)!!!\n",
					chId,
					pChStatus->vipInstId, pChStatus->chId, pChStatus->frameWidth,
					pChStatus->frameHeight,
					1000000 / pChStatus->frameInterval,
					pChStatus->isInterlaced);
		}
		else
		{
			printf (" DEMO: %2d: No video detected at CH [%d,%d] !!!\n",
					chId, pChStatus->vipInstId, pChStatus->chId);

		}
	}

	printf(" \n");

	return 0;
}

int Demo_captureGetTamperStatus(Ptr pPrm)
{
	AlgLink_ScdChStatus *pScdStat = (AlgLink_ScdChStatus *)pPrm;

	if(pScdStat->frmResult == ALG_LINK_SCD_DETECTOR_CHANGE)
	{
		printf(" [TAMPER DETECTED] %d: SCD CH <%d> CAP CH = %d \n", OSA_getCurTimeInMsec(), pScdStat->chId, Demo_captureGetCaptureChNum(pScdStat->chId));
	}
	else if(pScdStat->frmResult == ALG_LINK_SCD_DETECTOR_NO_CHANGE)
	{
		printf(" [TAMPER REMOVED] %d: SCD CH <%d> CAP CH = %d \n", OSA_getCurTimeInMsec(), pScdStat->chId, Demo_captureGetCaptureChNum(pScdStat->chId));
	}

	return 0;
}

int Demo_captureGetMotionStatus(Ptr pPrm)
{
	AlgLink_ScdResult *pScdResult = (AlgLink_ScdResult *)pPrm;

	printf(" [MOTION DETECTED] %d: SCD CH <%d> CAP CH = %d \n", OSA_getCurTimeInMsec(), pScdResult->chId, Demo_captureGetCaptureChNum(pScdResult->chId));

	return 0;
}

static void printResolution(UInt32 res)
{
	switch (res)
	{
		case VSYS_STD_1080P_60:
			printf("1080P60");
			break;
		case VSYS_STD_1080P_50:
			printf("1080P50");
			break;
		case VSYS_STD_720P_60:
			printf("720P60");
			break;
		case VSYS_STD_XGA_60:
			printf("XGA");
			break;
		case VSYS_STD_SXGA_60:
			printf("SXGA");
			break;
	}

}

int Demo_decodeErrorStatus(Ptr pPrm)
{

	int errBits;
	int firstTime = 1;
	VDEC_CH_ERROR_MSG * decodeErrMsg = (VDEC_CH_ERROR_MSG *) pPrm;
	int chId;
	int decodeErr;

	chId      = decodeErrMsg->chId;
	decodeErr = decodeErrMsg->errorMsg;

	for(errBits = 0; errBits < 32; errBits++)
	{
		if(decodeErr & (1 << errBits))
		{
			{
				if(firstTime)
				{
					//          printf("Error Name: \t BitPositon in ErrorMessage\n");
					firstTime = 0;
				}
				printf("[DECODER ERROR] %d: DECODE CH <%d> ERROR: %s \n"
						, OSA_getCurTimeInMsec(), chId, gDecoderErrorStrings[errBits].errorName);           
			}
		}
	}

	return 0;
}

	static
Void  Demo_printSlaveCoreExceptionContext(VSYS_SLAVE_CORE_EXCEPTION_INFO_S *excInfo)
{
	FILE *fpCcsCrashDump;
	char crashDumpFileName[100];

	printf("\n\n%d:!!!SLAVE CORE DOWN!!!.EXCEPTION INFO DUMP\n",OSA_getCurTimeInMsec());
	printf("\n !!HW EXCEPTION ACTIVE (0/1): [%d]\n",excInfo->exceptionActive);
	printf("\n !!EXCEPTION CORE NAME      : [%s]\n",excInfo->excCoreName);
	printf("\n !!EXCEPTION TASK NAME      : [%s]\n",excInfo->excTaskName);
	printf("\n !!EXCEPTION LOCATION       : [%s]\n",excInfo->excSiteInfo);
	printf("\n !!EXCEPTION INFO           : [%s]\n",excInfo->excInfo);
	snprintf(crashDumpFileName, sizeof(crashDumpFileName),"CCS_CRASH_DUMP_%s.txt",excInfo->excCoreName);
	fpCcsCrashDump = fopen(crashDumpFileName,"w");
	if (fpCcsCrashDump)
	{
		Demo_CCSCrashDumpFormatSave(excInfo,fpCcsCrashDump);
		fclose(fpCcsCrashDump);
		printf("\n !!EXCEPTION CCS CRASH DUMP FORMAT FILE STORED @ ./%s\n",crashDumpFileName);
	}
}

static int Demo_handleHdmiDviDisplays(void)
{
	int status;
	UInt32 highestRes;
	/* 1. Get the parsed EDID 
	   2. Check if current resolution is supported
	   3. Switch if required 
	   */
	status = Vdis_getScreenInfo(VDIS_DEV_HDMI, &gScrInfo);

	while (status == 0)
	{
		if (gScrInfo.isSinkConnected != TRUE)
		{
			printf(" DEMO: WARNING: TV/Monitor not detected !!!\n");
			break;
		}
		if (gScrInfo.isStreaming != TRUE)
		{
			printf(" DEMO: WARNING: HDMI Not streaming !!!\n");
			break;
		}
		if (gScrInfo.isHdmi == TRUE)
		{
			printf(" DEMO: TV Detected - HDMI interface !!!\n");
			if ((gScrInfo.resolution1 ==  VSYS_STD_1080P_60) || 
					(gScrInfo.resolution2 ==  VSYS_STD_1080P_60) || 
					(gScrInfo.resolution3 ==  VSYS_STD_1080P_60))
			{
				highestRes =  VSYS_STD_1080P_60;
			}
			else if ((gScrInfo.resolution1 ==  VSYS_STD_1080P_50) || 
					(gScrInfo.resolution2 ==  VSYS_STD_1080P_50) || 
					(gScrInfo.resolution3 ==  VSYS_STD_1080P_50))
			{
				highestRes =  VSYS_STD_1080P_50;
			}
			else if ((gScrInfo.resolution1 ==  VSYS_STD_720P_60) || 
					(gScrInfo.resolution2 ==  VSYS_STD_720P_60) || 
					(gScrInfo.resolution3 ==  VSYS_STD_720P_60))
			{
				highestRes =  VSYS_STD_720P_60;
			}
			else
			{
				highestRes =  VSYS_STD_1080P_60;
				printf(" DEMO: WARNING: TV might not support "
						"1080P60, 1080P50 & 720P60 !!!\n");
			}
		}
		else
		{
			printf(" DEMO: Monitor Detected - DVI interface !!!\n");
			if ((gScrInfo.resolution1 ==  VSYS_STD_SXGA_60) || 
					(gScrInfo.resolution2 ==  VSYS_STD_SXGA_60))
			{
				highestRes =  VSYS_STD_SXGA_60;
			}
			else if ((gScrInfo.resolution1 ==  VSYS_STD_XGA_60) || 
					(gScrInfo.resolution2 ==  VSYS_STD_XGA_60))
			{
				highestRes =  VSYS_STD_XGA_60;
			}
			else
			{
				highestRes =  VSYS_STD_SXGA_60;
				printf(" DEMO: WARNING: TV might not support SXGA & XGA !!!\n");
			}
		}

		if ((gScrInfo.currentResolution != gScrInfo.resolution1) && 
				(gScrInfo.currentResolution != gScrInfo.resolution2) && 
				(gScrInfo.currentResolution != gScrInfo.resolution3))
		{
			printf(" ################################ DEMO: INFO :");
			printResolution(gScrInfo.currentResolution);

			printf(" Resolution is not supported by sink !!!\n");
			printf(" Switching to ");
			printResolution(highestRes);
			printf(" !!!\n");
			__SpitSetCompositorCommon(VDIS_DEV_HDMI, highestRes);
		} 
		else
		{
			printf(" DEMO: INFO : Resolution set to ");
			printResolution(gScrInfo.currentResolution);
			printf(" !!!\n");
		}
		break;
	}

	return status;
}

int Demo_captureGetCaptureChNum (int scdChNum)
{
	int newChNum = scdChNum;
	VSYS_PARAMS_S contextInfo;

	Vsys_getContext(&contextInfo);
	/*
	   if ((contextInfo.systemUseCase == VSYS_USECASE_MULTICHN_VCAP_VENC)
	   || (contextInfo.systemUseCase == VSYS_USECASE_MULTICHN_PROGRESSIVE_VCAP_VDIS_VENC_VDEC_D1_AND_CIF)
	   || (contextInfo.systemUseCase == VSYS_USECASE_MULTICHN_PROGRESSIVE_VCAP_VDIS_VENC_VDEC_8CH)
	   || (contextInfo.systemUseCase == VSYS_USECASE_MULTICHN_PROGRESSIVE_VCAP_VDIS_VENC_VDEC_4CH)
	   )
	   */
	if(scdChNum >= Vcap_getNumChannels())
	{
		newChNum -=   Vcap_getNumChannels();
	}
	/* Please add for other usecase */
	return newChNum;
}

Int32 Debug_eventHandler(UInt32 eventId, Ptr pPrm, Ptr appData)
{
	printf("=> Enter %s: event ID %d\n", __FUNCTION__, eventId);

	if(eventId==VSYS_EVENT_VIDEO_DETECT)
	{
		printf(" \n");
		printf(" DEMO: Received event VSYS_EVENT_VIDEO_DETECT [0x%04x]\n", eventId);

		Demo_captureGetVideoSourceStatus();
	}

	if(eventId==VSYS_EVENT_TAMPER_DETECT)
	{
		Demo_captureGetTamperStatus(pPrm);
	}

	if(eventId==VSYS_EVENT_MOTION_DETECT)
	{
		Demo_captureGetMotionStatus(pPrm);
	}

	if(eventId== VSYS_EVENT_DECODER_ERROR)
	{
		Demo_decodeErrorStatus(pPrm);
	}

	if (eventId == VSYS_EVENT_SLAVE_CORE_EXCEPTION)
	{
		Demo_printSlaveCoreExceptionContext(pPrm);
	}

	if(eventId==VSYS_EVENT_HDMI_TV_DISCONNECTED)
	{
		printf(" DEMO: WARNING: HDMI TV/Monitor disconnected !!!\n");
		gIsSinkDetected = FALSE;
	}

	if(eventId==VSYS_EVENT_HDMI_TV_CONNECTED)
	{
		printf(" DEMO: HDMI TV/Monitor connected !!!\n");
		Demo_handleHdmiDviDisplays();
		gIsSinkDetected = TRUE;
	}



	return 0;
}



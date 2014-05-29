#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "decode.h"
#include "encode.h"
#include "split.h"

#include "../src/common_sdk.h"
#include "../src/common/system_def.h"

//#include "../src/link/link_def.h"

SystemVideo_Ivahd2ChMap_Tbl systemVid_encDecIvaChMapTbl_test =
{
	.isPopulated = 1,
	.ivaMap[0] =
	{
		.EncNumCh  = 4,
		.EncChList = {0, 3, 6, 9,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.DecNumCh  = 4,
		.DecChList = {2, 5, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	.ivaMap[1] =
	{
		.EncNumCh  = 4,
		.EncChList = {1, 4, 7, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.DecNumCh  = 4,
		.DecChList = {1, 4, 7, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	.ivaMap[2] =
	{
		.EncNumCh  = 4,
		.EncChList = {2, 5, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.DecNumCh  = 4,
		.DecChList = {0, 3, 6, 9,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
};

static char *gMultiCh_cpuName[SYSTEM_PLATFORM_CPU_REV_MAX] = {
	"ES1.0",
	"ES1.1",
	"ES2.0",
	"ES2.1",
	"UNKNOWN",
};

static int MultiCh_detectBoard_6800A1()
{
	int status;
	int cpuRev;

	SystemVpss_PlatformInfo  platformInfo;

	status = System_linkControl(
			SYSTEM_LINK_ID_M3VPSS
			, SYSTEM_M3VPSS_CMD_GET_PLATFORM_INFO
			, &platformInfo
			, sizeof(platformInfo)
			, TRUE
			);
	UTILS_assert(status==OSA_SOK);

	// Get CPU version
	cpuRev = platformInfo.cpuRev;			// sdk里面的api接口获取cpu版本号错误，正确的用dmesg里面查看。
	if (cpuRev >= SYSTEM_PLATFORM_CPU_REV_MAX)
	{
		cpuRev = SYSTEM_PLATFORM_CPU_REV_UNKNOWN;
	}
	printf(" %u: MCFW  : CPU Revision [%s] !!! \r\n", OSA_getCurTimeInMsec(), gMultiCh_cpuName[cpuRev]);

	return 0;
}


extern Int32 Debug_eventHandler(UInt32 eventId, Ptr pPrm, Ptr appData);
static void SystemInit_test_display()
{

	printf("============SystemInit entry.>>>>>>>>>>>>\n");
	VSYS_PARAMS_S vsysParams;
	VCAP_PARAMS_S vcapParams;
	VENC_PARAMS_S vencParams;
	VDEC_PARAMS_S vdecParams;
	VDIS_PARAMS_S vdisParams;

	Vsys_params_init(&vsysParams);
	Vcap_params_init(&vcapParams);
	Venc_params_init(&vencParams);
	Vdec_params_init(&vdecParams);
	Vdis_params_init(&vdisParams);

	vcapParams.numChn		= 0;
	vencParams.numPrimaryChn	= 0;
	vencParams.numSecondaryChn	= 0;
	vdecParams.numChn		= 0;
	vdisParams.numChannels		= 0;
	vsysParams.numChs		= 0;
	vsysParams.systemUseCase = 0;
	vsysParams.enableSecondaryOut = FALSE;
	vsysParams.enableNsf     = FALSE;
	vsysParams.enableCapture = FALSE;
	vsysParams.enableDecode  = FALSE;
	vsysParams.enableNullSrc = FALSE;
	vsysParams.enableOsd	 = FALSE;
	vsysParams.enableScd	 = FALSE;
	vsysParams.numDeis	 = 0;
	vsysParams.numSwMs	 = 0;
	vsysParams.numDisplays	 = 0;
	vsysParams.enableAVsync  = FALSE;

	vdisParams.deviceParams[VDIS_DEV_HDMI].resolution   = VSYS_STD_1080P_60;
	vdisParams.mosaicLayoutResolution[VDIS_DEV_HDMI] = vdisParams.deviceParams[VDIS_DEV_HDMI].resolution;
	vdisParams.enableLayoutGridDraw = FALSE;
	vdisParams.mosaicParams[0].userSetDefaultSWMLayout = TRUE;
	vdisParams.mosaicParams[1].userSetDefaultSWMLayout = TRUE;
	Vdis_tiedVencInit(VDIS_DEV_HDCOMP, VDIS_DEV_DVO2, &vdisParams);
	Vsys_enableFastUsecaseSwitch(FALSE);

	Vsys_init(&vsysParams);
	Vcap_init(&vcapParams);
	Venc_init(&vencParams);
	Vdec_init(&vdecParams);
	Vdis_init(&vdisParams);

	Vsys_configureDisplay();
	Vsys_registerEventHandler(Debug_eventHandler, NULL);

}

void display_link_test()
{
	SystemInit_test_display();
#if 1

	gVcapModuleContext.captureId	= SYSTEM_LINK_ID_CAPTURE;
	gVdisModuleContext.displayId[0] = SYSTEM_LINK_ID_DISPLAY_0; // ON CHIP HDMI

	printf("============System init links entry>>>>>>>>>>>>\n");
	CaptureLink_CreateParams    capturePrm;
	DupLink_CreateParams	    dupPrm;
	DisplayLink_CreateParams    displayPrm[VDIS_DEV_MAX];

	CaptureLink_VipInstParams *pCaptureInstPrm;
	CaptureLink_OutParams	  *pCaptureOutPrm;

	printf("MultiCh_createVcapVdis1() ver: %s, %s\n", __DATE__, __TIME__);


	UInt32 dupId;
	UInt32 vipInstId;
	UInt32 i;
	UInt32 numSubChains;

	dpline();
	MultiCh_detectBoard_6800A1();
	dpline();
	System_linkControl(SYSTEM_LINK_ID_M3VPSS, SYSTEM_M3VPSS_CMD_RESET_VIDEO_DEVICES, NULL, 0, TRUE);
	dpline();
	System_linkControl(SYSTEM_LINK_ID_M3VIDEO, SYSTEM_COMMON_CMD_SET_CH2IVAHD_MAP_TBL, &systemVid_encDecIvaChMapTbl_test, sizeof(SystemVideo_Ivahd2ChMap_Tbl), TRUE);
	dpline();


	for (i = 0; i < VDIS_DEV_MAX; i++)
	{
		MULTICH_INIT_STRUCT(DisplayLink_CreateParams,displayPrm[i]);
	}

	numSubChains		 = 1;
	CaptureLink_CreateParams_Init(&capturePrm);
	dpline();
	
	capturePrm.isPalMode			= FALSE;
	capturePrm.numVipInst			= 1 * numSubChains;

	capturePrm.tilerEnable			= FALSE;
	capturePrm.fakeHdMode			= FALSE;
	capturePrm.enableSdCrop			= FALSE;
	capturePrm.doCropInCapture		= FALSE;

	capturePrm.numExtraBufs			= 0;
	capturePrm.maxBlindAreasPerCh		= 0;
	capturePrm.overrideNumBufsInInstPrms	= 0;

	capturePrm.outQueParams[0].nextLink = SYSTEM_LINK_ID_DISPLAY_0;

	dpline();

	for(vipInstId=0; vipInstId<capturePrm.numVipInst; vipInstId++)
	{
		pCaptureInstPrm 		    = &capturePrm.vipInst[vipInstId];
		pCaptureInstPrm->vipInstId	    = SYSTEM_CAPTURE_INST_VIP0_PORTA;
		pCaptureInstPrm->videoDecoderId     = 0; /* DONT set it to TVP5158 */
		pCaptureInstPrm->standard           = SYSTEM_STD_1080P_30;
		pCaptureInstPrm->inDataFormat       = SYSTEM_DF_YUV422P;
		pCaptureInstPrm->numOutput          = 1;
		pCaptureInstPrm->videoCaptureMode	= DEVICE_CAPT_VIDEO_CAPTURE_MODE_SINGLE_CH_NON_MUX_EMBEDDED_SYNC;
		pCaptureInstPrm->videoIfMode		= SYSTEM_CAPT_VIDEO_IF_MODE_8BIT;

		pCaptureOutPrm                      = &pCaptureInstPrm->outParams[0];
		pCaptureOutPrm->dataFormat          = SYSTEM_DF_YUV422I_YUYV;
		pCaptureOutPrm->scEnable            = FALSE;
		pCaptureOutPrm->scOutWidth          = 0;
		pCaptureOutPrm->scOutHeight         = 0;
		pCaptureOutPrm->outQueId            = 0;

	}

	for(i=0; i<1; i++)
	{
		displayPrm[i].inQueParams[0].prevLinkId    = SYSTEM_LINK_ID_CAPTURE;
		displayPrm[i].inQueParams[0].prevLinkQueId = 0;
		displayPrm[i].displayRes		= gVdisModuleContext.vdisConfig.deviceParams[i].resolution;
	}
	dpline();

	System_linkCreate (SYSTEM_LINK_ID_CAPTURE, &capturePrm, sizeof(capturePrm));
	dpline();
	//MULTICH_CREATE_LINK(SYSTEM_VPSS_LINK_ID_DUP_0     , &dupPrm	 , sizeof(dupPrm));
	dpline();
	System_linkCreate(SYSTEM_LINK_ID_DISPLAY_0, &displayPrm[0], sizeof(displayPrm[0]));
	dpline();

	printf("============System init links leave<<<<<<<<<<<<\n");

	/* Start components in reverse order */
	Vdis_start();
	//Venc_start();
	Vcap_start();
	//Vdec_start();
#endif
}



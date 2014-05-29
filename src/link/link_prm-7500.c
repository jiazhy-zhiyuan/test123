#include "link_def-7500.h"

extern int g_standard[];
#define ETAH_1080P30

SystemVideo_Ivahd2ChMap_Tbl systemVid_encDecIvaChMapTbl_7500 =
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

Void multich_hddvr_set_capture_prm_7500(CaptureLink_CreateParams *capturePrm)
{
	CaptureLink_VipInstParams         *pCaptureInstPrm;
	CaptureLink_OutParams             *pCaptureOutPrm;
	UInt32 vipInstId;

	capturePrm->isPalMode                   = FALSE;
	capturePrm->numVipInst                  = g_dev.vi_channel_num;
	capturePrm->tilerEnable                 = FALSE;
	capturePrm->fakeHdMode                  = FALSE;
	capturePrm->enableSdCrop                = FALSE;
	capturePrm->doCropInCapture             = FALSE;
	capturePrm->numBufsPerCh                = NUM_BUFS_PER_CH_CAPTURE_7500;
	capturePrm->numExtraBufs                = 0;
	capturePrm->maxBlindAreasPerCh          = 0;
	capturePrm->overrideNumBufsInInstPrms   = 0;

#if 0
	for(vipInstId=0; vipInstId<capturePrm->numVipInst; vipInstId++)
	{
		pCaptureInstPrm                     = &capturePrm->vipInst[vipInstId];
		pCaptureInstPrm->vipInstId          = (SYSTEM_CAPTURE_INST_VIP0_PORTA+  vipInstId)%SYSTEM_CAPTURE_INST_MAX;
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
#else
	// 前面板丝印调整: 2,3,4,1，对应的程序需要修改, 赵幸: 2014.2.11
	for(vipInstId=0; vipInstId<capturePrm->numVipInst; vipInstId++)
	{
		pCaptureInstPrm                     = &capturePrm->vipInst[vipInstId];
		switch(vipInstId) {
			case 0:
				pCaptureInstPrm->vipInstId = SYSTEM_CAPTURE_INST_VIP0_PORTA;
				break;
			case 1:
				pCaptureInstPrm->vipInstId = SYSTEM_CAPTURE_INST_VIP0_PORTB; //SYSTEM_CAPTURE_INST_VIP1_PORTB;
				break;
			case 2:
				pCaptureInstPrm->vipInstId = SYSTEM_CAPTURE_INST_VIP1_PORTA;
				break;
			case 3:
				pCaptureInstPrm->vipInstId = SYSTEM_CAPTURE_INST_VIP0_PORTB;
				break;
			default:
				break;
		}
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
#endif
}

Void multich_hddvr_set_dei_prm_7500(DeiLink_CreateParams *deiPrm, DeiLink_OutputScaleFactor *outScalerFactorDeiSc, DeiLink_OutputScaleFactor *outScalerFactorVipSc)
{
	UInt32 i, outId, chId;
	UInt32 outIdList[] = { DEI_LINK_OUT_QUE_DEI_SC, DEI_LINK_OUT_QUE_VIP_SC };


	deiPrm->comprEnable                 = FALSE;
	deiPrm->setVipScYuv422Format        = FALSE;
	deiPrm->inputDeiFrameRate           = 30;
	deiPrm->outputDeiFrameRate          = 30;
	deiPrm->enableDeiForceBypass        = TRUE;
	deiPrm->enableForceInterlacedInput  = FALSE;
	deiPrm->enableLineSkipSc            = FALSE;
	deiPrm->enableDualVipOut            = FALSE;
	deiPrm->enableInputFrameRateUpscale = FALSE;

	for(i=0; i<OSA_ARRAYSIZE(outIdList); i++)
	{
		outId = outIdList[i];

		deiPrm->enableOut[outId] = TRUE;

		deiPrm->tilerEnable[outId] = FALSE;
		if(outId==DEI_LINK_OUT_QUE_VIP_SC)
			deiPrm->tilerEnable[outId] = TILER_ENABLE_ENCODE_7500;

		for(chId=0; chId<DEI_LINK_MAX_CH; chId++)
		{
			if(outId==DEI_LINK_OUT_QUE_VIP_SC)
				deiPrm->outScaleFactor[outId][chId] = *outScalerFactorVipSc;
			if(outId==DEI_LINK_OUT_QUE_DEI_SC)
				deiPrm->outScaleFactor[outId][chId] = *outScalerFactorDeiSc;
		}

		deiPrm->inputFrameRate[outId]   = 30;
		deiPrm->outputFrameRate[outId]  = 30;

		deiPrm->numBufsPerCh[outId]     = NUM_BUFS_PER_CH_DEI_7500;
		deiPrm->generateBlankOut[outId] = FALSE;
	}
}


Void multich_set_capture_fps_7500(UInt32 *captureFps)
{
	Bool isPal = Vcap_isPalMode();

	if (isPal)
	{
		*captureFps = 50;
	}
	else
	{
		*captureFps = 60;
	}
}

Void multich_register_created_link_7500(MultiChHdDvr_Context_7500 *pContext, UInt32 linkID)
{
	OSA_assert(pContext->createdLinkCount < OSA_ARRAYSIZE(pContext->createdLinks));
	pContext->createdLinks[pContext->createdLinkCount] = linkID;
	pContext->createdLinkCount++;
}

#define SYSTEM_SW_MS_SC_INST_DEIHQ_SC_7500        (1)
#define SYSTEM_SW_MS_SC_INST_DEI_SC_7500          (2)
#define SYSTEM_SW_MS_SC_INST_VIP0_SC_7500         (3)
#define SYSTEM_SW_MS_SC_INST_VIP1_SC_7500         (4)
#define SYSTEM_SW_MS_SC_INST_SC5_7500             (5)
#define SYSTEM_SW_MS_SC_INST_DEIHQ_SC_NO_DEI_7500 (6)
#define SYSTEM_SW_MS_SC_INST_DEI_SC_NO_DEI_7500   (7)

#define	MULTICH_MAX_USECASE_MAX_NUM_LINKS_7500		(64)
#define	MULTICH_MAX_NUM_CAPTURE_DEVICES_7500			(4)
#define MULTICH_NUM_CAPTURE_BUFFERS_7500			(8)

#define MULTICH_NUM_SWMS_0_BUFFERS_7500			(8)
#define MULTICH_NUM_SWMS_1_BUFFERS_7500			(8)
#define MULTICH_NUM_SWMS_2_BUFFERS_7500			(8)
#define MULTICH_NUM_SWMS_3_BUFFERS_7500			(8)
// 最大可以5个拼接器: 3, 4, 5, 6, 7
Void multich_set_swms_prm_7500(UInt32 swMsId)
{
	g_swms[swMsId].maxOutRes			= VSYS_STD_720P_60;
	g_swms[swMsId].initOutRes			= VSYS_STD_720P_60;
#ifdef ETAH_1080P30
	g_swms[swMsId].maxOutRes			= VSYS_STD_1080P_30;
	g_swms[swMsId].initOutRes			= VSYS_STD_1080P_30;
#endif

	VIDEO_RECT  rects[1];
	switch(swMsId) {
		case 0:
		{
			g_swms[swMsId].numSwMsInst		= 1;
			g_swms[swMsId].swMsInstId[0]		= SYSTEM_SW_MS_SC_INST_SC5_7500;	// SYSTEM_SW_MS_SC_INST_SC5
			g_swms[swMsId].maxInputQueLen		= SYSTEM_SW_MS_DEFAULT_INPUT_QUE_LEN + 6;
			g_swms[swMsId].numOutBuf		= NUM_BUFS_PER_CH_SWMS_7500;
			g_swms[swMsId].enableProcessTieWithDisplay	= TRUE;
			
			break;
		}
		case 1:
		{
			g_swms[swMsId].numSwMsInst		= 1;
			g_swms[swMsId].swMsInstId[0]		= SYSTEM_SW_MS_SC_INST_DEI_SC_NO_DEI_7500;
			g_swms[swMsId].maxInputQueLen		= SYSTEM_SW_MS_DEFAULT_INPUT_QUE_LEN + 6;
			g_swms[swMsId].numOutBuf		= NUM_BUFS_PER_CH_SWMS_7500;
			g_swms[swMsId].includeVipScInDrvPath		= TRUE;
			g_swms[swMsId].enableProcessTieWithDisplay	= TRUE;

			break;
		}
		case 2:
		{
			g_swms[swMsId].numSwMsInst		= 1;
			g_swms[swMsId].swMsInstId[0]		= SYSTEM_SW_MS_SC_INST_DEIHQ_SC_NO_DEI_7500;
			//g_swms[swMsId].swMsInstId[0]		= SYSTEM_SW_MS_SC_INST_SC5;
			g_swms[swMsId].maxInputQueLen		= 13;
			g_swms[swMsId].numOutBuf		= 4;
			g_swms[swMsId].includeVipScInDrvPath		= TRUE;
			g_swms[swMsId].enableProcessTieWithDisplay	= TRUE;
			g_swms[swMsId].maxOutRes			= ETAH_DISPLAY_STD_NTSC;
			g_swms[swMsId].initOutRes			= ETAH_DISPLAY_STD_NTSC;
			break;
		}
		case 3:
		{
			g_swms[swMsId].numSwMsInst		= 1;
			g_swms[swMsId].swMsInstId[0]		= SYSTEM_SW_MS_SC_INST_DEI_SC_NO_DEI_7500;
			g_swms[swMsId].maxInputQueLen		= 6;
			g_swms[swMsId].numOutBuf		= MULTICH_NUM_SWMS_3_BUFFERS_7500;
			g_swms[swMsId].enableProcessTieWithDisplay	= FALSE;
			break;
		}
		default:
		{
			break;
		}
	}

	g_swms[swMsId].lineSkipMode			= FALSE;
	g_swms[swMsId].enableLayoutGridDraw		= FALSE;
	g_swms[swMsId].enableOuputDup			= TRUE;
	g_swms[swMsId].outputBufModified		= TRUE;

	SwMsLink_LayoutPrm *layoutInfo = &g_swms[swMsId].layoutPrm;
	layoutInfo->onlyCh2WinMapChanged = FALSE;
	layoutInfo->outputFPS = 30;
	layoutInfo->numWin = 16;

	//int i;
	////for(i = layoutInfo->numWin; i < SWMS_MAX_WIN_PER_LINK; i++) {
	//	memset(&g_swms[swMsId].layoutPrm.winInfo[i], 0x0, sizeof(SwMsLink_LayoutWinInfo));
	//}

}


Void multich_set_sd_display_res_7500(VSYS_VIDEO_STANDARD_E resolution)
{
	/* Work around for VENC tying getting broken when using sysfs cmd to change resolution */
	Vdis_sysfsCmd(3, VDIS_SYSFSCMD_SET_GRPX, VDIS_SYSFS_GRPX0, VDIS_OFF);
	Vdis_sysfsCmd(3, VDIS_SYSFSCMD_SET_GRPX, VDIS_SYSFS_GRPX1, VDIS_OFF);

	Vdis_setResolution(VDIS_DEV_SD,resolution);

	Vdis_sysfsCmd(3, VDIS_SYSFSCMD_SET_GRPX, VDIS_SYSFS_GRPX0, VDIS_ON);
	Vdis_sysfsCmd(3, VDIS_SYSFSCMD_SET_GRPX, VDIS_SYSFS_GRPX1, VDIS_ON);

}

Void multich_set_display_prms_7500(DisplayLink_CreateParams *displayPrm, int displayId)
{
	if (Vcap_isPalMode() && (Vdis_getResolution(VDIS_DEV_SD) != VSYS_STD_PAL))
	{
		multich_set_sd_display_res_7500(VSYS_STD_PAL);
	}

	displayPrm->displayRes = gVdisModuleContext.vdisConfig.deviceParams[VDIS_DEV_SD].resolution;
}



//#define     NUM_BUFS_PER_CH_ENC_PRI              (4)
//#define     NUM_BUFS_PER_CH_ENC_SEC              (4)

Void multich_set_enclink_prm_7500(EncLink_CreateParams *encPrm)
{
	int i;

	encPrm->numBufPerCh[ENC_LINK_SECONDARY_STREAM_POOL_ID_7500] = NUM_BUFS_PER_CH_ENC_SEC_7500;
	encPrm->numBufPerCh[ENC_LINK_PRIMARY_STREAM_POOL_ID_7500] = NUM_BUFS_PER_CH_ENC_PRI_7500;

	gVencModuleContext.vencConfig.numPrimaryChn = 4;
	for (i = 0; i < gVencModuleContext.vencConfig.numPrimaryChn; i++)
	{
		EncLink_ChCreateParams		*pLinkChPrm	= &encPrm->chCreateParams[i];
		EncLink_ChDynamicParams		*pLinkDynPrm	= &pLinkChPrm->defaultDynamicParams;
		VENC_CHN_PARAMS_S		*pChPrm		= &gVencModuleContext.vencConfig.encChannelParams[i];
		VENC_CHN_DYNAMIC_PARAM_S	*pDynPrm	= &pChPrm->dynamicParam;

		pLinkChPrm->format			= IVIDEO_H264HP;
		pLinkChPrm->profile			= gVencModuleContext.vencConfig.h264Profile[i];
		pLinkChPrm->dataLayout			= IVIDEO_FIELD_SEPARATED;
		pLinkChPrm->fieldMergeEncodeEnable	= FALSE;
		pLinkChPrm->enableAnalyticinfo		= FALSE;
		pLinkChPrm->maxBitRate			= pChPrm->maxBitRate;
		pLinkChPrm->encodingPreset		= pChPrm->encodingPreset;
		pLinkChPrm->rateControlPreset		= pChPrm->rcType;
		pLinkChPrm->enableHighSpeed		= TRUE;
		pLinkChPrm->enableSVCExtensionFlag	= pChPrm->enableSVCExtensionFlag;
		pLinkChPrm->numTemporalLayer		= pChPrm->numTemporalLayer;

		pLinkDynPrm->intraFrameInterval		= pDynPrm->intraFrameInterval;
		pLinkDynPrm->targetBitRate		= 2000000;//pDynPrm->targetBitRate;
		pLinkDynPrm->interFrameInterval		= 1;
		pLinkDynPrm->mvAccuracy 		= IVIDENC2_MOTIONVECTOR_QUARTERPEL;
		pLinkDynPrm->inputFrameRate		= pDynPrm->inputFrameRate;
		pLinkDynPrm->rcAlg			= pDynPrm->rcAlg;
		pLinkDynPrm->qpMin			= pDynPrm->qpMin;
		pLinkDynPrm->qpMax			= pDynPrm->qpMax;
		pLinkDynPrm->qpInit			= pDynPrm->qpInit;
		pLinkDynPrm->vbrDuration		= pDynPrm->vbrDuration;
		pLinkDynPrm->vbrSensitivity		= pDynPrm->vbrSensitivity;

		//channel: 0, profile: 100, enableAnalyticinfo: 0, enableWaterMarking: 0, maxBitRate: -1, encodingPreset: 3, 
		// rateControlPreset: 0, enableSVCExtensionFlag: 0, numTemporalLayer: 1
		//	dynPrm: intraFrameInterval: 30, targetBitRate: 2000000, inputFrameRate: 30, rcAlg: 0, qpMin: 10, qpMax: 40, 
		//	qpInit: -1, vbrDuration: 8, vbrSensitivity: 0
		printf( "channel: %d, profile: %d, enableAnalyticinfo: %d, enableWaterMarking: %d, maxBitRate: %d, "
				"encodingPreset: %d, rateControlPreset: %d, enableSVCExtensionFlag: %d, numTemporalLayer: %d\n"
				, i
				, pLinkChPrm->profile
				, pLinkChPrm->enableAnalyticinfo
				, pLinkChPrm->enableWaterMarking
				, pLinkChPrm->maxBitRate
				, pLinkChPrm->encodingPreset
				, pLinkChPrm->rateControlPreset
				, pLinkChPrm->enableSVCExtensionFlag
				, pLinkChPrm->numTemporalLayer
		      );
		printf( "\tdynPrm: intraFrameInterval: %d, targetBitRate: %d, inputFrameRate: %d, rcAlg: %d, "
				"qpMin: %d, qpMax: %d, qpInit: %d, vbrDuration: %d, vbrSensitivity: %d\n"
				, pLinkDynPrm->intraFrameInterval
				, pLinkDynPrm->targetBitRate
				, pLinkDynPrm->inputFrameRate
				, pLinkDynPrm->rcAlg
				, pLinkDynPrm->qpMin
				, pLinkDynPrm->qpMax
				, pLinkDynPrm->qpInit
				, pLinkDynPrm->vbrDuration
				, pLinkDynPrm->vbrSensitivity
		      );
	}
}

#define TILER_ENABLE_DECODE      (TRUE)
#define TILER_ENABLE_ENCODE      (TRUE)

Void multich_set_dei_prm_7500(DeiLink_CreateParams *deiPrm, DeiLink_OutputScaleFactor *outScalerFactorDeiSc, DeiLink_OutputScaleFactor *outScalerFactorVipSc)
{
	UInt32 i, outId, chId;
	//UInt32 outIdList[] = { DEI_LINK_OUT_QUE_DEI_SC, DEI_LINK_OUT_QUE_VIP_SC };
	//UInt32 outIdList[] = { 0 };

	deiPrm->comprEnable                 = FALSE;
	deiPrm->setVipScYuv422Format        = FALSE;
	deiPrm->inputDeiFrameRate           = 30;
	deiPrm->outputDeiFrameRate          = 30;
	deiPrm->enableDeiForceBypass        = FALSE;
	deiPrm->enableForceInterlacedInput  = TRUE;
	deiPrm->enableLineSkipSc            = FALSE;
	deiPrm->enableDualVipOut            = FALSE;
	deiPrm->enableInputFrameRateUpscale = FALSE;

	for(i=0; i<1; i++)
	{
		outId = 0;

		deiPrm->enableOut[outId] = TRUE;
		deiPrm->tilerEnable[outId] = FALSE;
		deiPrm->tilerEnable[outId] = TILER_ENABLE_ENCODE_7500;

		for(chId=0; chId<DEI_LINK_MAX_CH; chId++)
		{
			deiPrm->outScaleFactor[outId][chId] = *outScalerFactorVipSc;
		}

		deiPrm->inputFrameRate[outId]   = 30;
		deiPrm->outputFrameRate[outId]  = 30;

		deiPrm->numBufsPerCh[outId]     = NUM_BUFS_PER_CH_DEI_7500;
		deiPrm->generateBlankOut[outId] = FALSE;
	}
}

Void multich_hddvr_set_nsf_prm_7500(NsfLink_CreateParams * nsfPrm, UInt32 numBufPerCh, UInt32 outputFrameRate)
{
	nsfPrm->numOutQue    = 1;
	nsfPrm->bypassNsf    = TRUE;
	nsfPrm->tilerEnable  = FALSE;
	nsfPrm->numBufsPerCh = numBufPerCh;
	nsfPrm->inputFrameRate = 30;
	nsfPrm->outputFrameRate = outputFrameRate;
}

Void multich_set_nsf_prm_7500(NsfLink_CreateParams * nsfPrm, UInt32 numBufPerCh, UInt32 outputFrameRate)
{
	nsfPrm->numOutQue    = 1;
	nsfPrm->bypassNsf    = TRUE;
	nsfPrm->tilerEnable  = FALSE;
	nsfPrm->numBufsPerCh = numBufPerCh;
	nsfPrm->inputFrameRate = 30;
	nsfPrm->outputFrameRate = outputFrameRate;
}

Void multich_hddvr_set_enclink_prm_7500(EncLink_CreateParams *encPrm)
{
	int i,j;
	EncLink_ChCreateParams *pLinkChPrm;
	EncLink_ChDynamicParams *pLinkDynPrm;
	VENC_CHN_DYNAMIC_PARAM_S *pDynPrm;
	VENC_CHN_PARAMS_S *pChPrm;

	encPrm->numBufPerCh[ENC_LINK_SECONDARY_STREAM_POOL_ID_7500] = NUM_BUFS_PER_CH_ENC_SEC_7500;
	encPrm->numBufPerCh[ENC_LINK_PRIMARY_STREAM_POOL_ID_7500]   = NUM_BUFS_PER_CH_ENC_PRI_7500;

	gVencModuleContext.vencConfig.numPrimaryChn   = g_dev.vi_channel_num + g_dev.swms_encode_num + 1;
	gVencModuleContext.vencConfig.numPrimaryChn   = (g_dev.vi_channel_num + g_dev.swms_encode_num) * g_dev.stream_type;
	//gVencModuleContext.vencConfig.numSecondaryChn = g_dev.vi_channel_num + g_dev.swms_encode_num;
	//gVencModuleContext.vencConfig.numSecondaryChn = 1;			// 只有导播需要次码流
	gVencModuleContext.vencConfig.numSecondaryChn = 0;

	printf("=========================(vi_channel_num: %d, swms_encode_num: %d) enclink, primary: %d, second: %d\n"
		, g_dev.vi_channel_num
		, g_dev.swms_encode_num
		, gVencModuleContext.vencConfig.numPrimaryChn
		, gVencModuleContext.vencConfig.numSecondaryChn);

	/* Primary Stream Params - D1 */
	for (i=0; i < gVencModuleContext.vencConfig.numPrimaryChn; i++)
	{
		pLinkChPrm  = &encPrm->chCreateParams[i];
		pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

		pChPrm      = &gVencModuleContext.vencConfig.encChannelParams[i];
		pDynPrm     = &pChPrm->dynamicParam;

		pLinkChPrm->format                  = IVIDEO_H264HP;
		pLinkChPrm->profile                 = gVencModuleContext.vencConfig.h264Profile[i];
		pLinkChPrm->dataLayout              = VCODEC_FIELD_SEPARATED;
		pLinkChPrm->fieldMergeEncodeEnable  = FALSE;
		pLinkChPrm->enableAnalyticinfo      = FALSE;
		pLinkChPrm->maxBitRate              = pChPrm->maxBitRate;
		pLinkChPrm->encodingPreset          = pChPrm->encodingPreset;
		pLinkChPrm->rateControlPreset       = pChPrm->rcType;
		pLinkChPrm->enableHighSpeed         = TRUE;
		pLinkChPrm->numTemporalLayer        = VENC_TEMPORAL_LAYERS_2;
		pLinkChPrm->enableSVCExtensionFlag  = pChPrm->enableSVCExtensionFlag;

		pLinkDynPrm->intraFrameInterval     = pDynPrm->intraFrameInterval;
		pLinkDynPrm->targetBitRate          = pDynPrm->targetBitRate;
		pLinkDynPrm->interFrameInterval     = 1;
		pLinkDynPrm->mvAccuracy             = IVIDENC2_MOTIONVECTOR_QUARTERPEL;
		pLinkDynPrm->inputFrameRate         = pDynPrm->inputFrameRate;
		pLinkDynPrm->rcAlg                  = pDynPrm->rcAlg;
		pLinkDynPrm->qpMin                  = pDynPrm->qpMin;
		pLinkDynPrm->qpMax                  = pDynPrm->qpMax;
		pLinkDynPrm->qpInit                 = pDynPrm->qpInit;
		pLinkDynPrm->vbrDuration            = pDynPrm->vbrDuration;
		pLinkDynPrm->vbrSensitivity         = pDynPrm->vbrSensitivity;
	}
#if 0
	/* Secondary Out <CIF> Params */
	for (i =  gVencModuleContext.vencConfig.numPrimaryChn,
			j =  VENC_PRIMARY_CHANNELS;
			i < (gVencModuleContext.vencConfig.numPrimaryChn
				+ gVencModuleContext.vencConfig.numSecondaryChn);
			i++, j++)
	{
		pLinkChPrm  = &encPrm->chCreateParams[i];
		pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

		pChPrm      = &gVencModuleContext.vencConfig.encChannelParams[j];
		pDynPrm     = &pChPrm->dynamicParam;

		pLinkChPrm->format                  = IVIDEO_H264HP;
		pLinkChPrm->profile                 = gVencModuleContext.vencConfig.h264Profile[i];
		pLinkChPrm->dataLayout              = VCODEC_FIELD_SEPARATED;
		pLinkChPrm->fieldMergeEncodeEnable  = FALSE;
		pLinkChPrm->enableAnalyticinfo      = pChPrm->enableAnalyticinfo;
		pLinkChPrm->maxBitRate              = pChPrm->maxBitRate;
		pLinkChPrm->encodingPreset          = pChPrm->encodingPreset;
		pLinkChPrm->rateControlPreset       = pChPrm->rcType;
		pLinkChPrm->enableHighSpeed         = TRUE;
		pLinkChPrm->numTemporalLayer        = VENC_TEMPORAL_LAYERS_2;
		pLinkChPrm->enableSVCExtensionFlag  = pChPrm->enableSVCExtensionFlag;


		pLinkDynPrm->intraFrameInterval     = pDynPrm->intraFrameInterval;
		pLinkDynPrm->targetBitRate          = pDynPrm->targetBitRate;
		pLinkDynPrm->interFrameInterval     = 1;
		pLinkDynPrm->mvAccuracy             = IVIDENC2_MOTIONVECTOR_QUARTERPEL;
		pLinkDynPrm->inputFrameRate         = pDynPrm->inputFrameRate;
		pLinkDynPrm->qpMin                  = pDynPrm->qpMin;
		pLinkDynPrm->qpMax                  = pDynPrm->qpMax;
		pLinkDynPrm->qpInit                 = pDynPrm->qpInit;
		pLinkDynPrm->vbrDuration            = pDynPrm->vbrDuration;
		pLinkDynPrm->vbrSensitivity         = pDynPrm->vbrSensitivity;
	}
#endif
}

Void multich_hddvr_set_ipcbitsout_hlos_prms_7500(IpcBitsOutLinkHLOS_CreateParams * ipcBitsOutHostPrm)
{
	int i;

	for (i = 0; i < g_dev.decode_channel_num; i++) {
		System_LinkChInfo *pChInfo;

		pChInfo = &ipcBitsOutHostPrm->inQueInfo.chInfo[i];
		pChInfo->bufType        = 0; // NOT USED
		pChInfo->codingformat   = 0; // NOT USED
		pChInfo->dataFormat     = 0; // NOT USED
		pChInfo->memType        = 0; // NOT USED
		pChInfo->startX         = 0; // NOT USED
		pChInfo->startY         = 0; // NOT USED
		pChInfo->width          = g_dev.decode_max_width;
		pChInfo->height         = g_dev.decode_max_height;
		pChInfo->pitch[0]       = 0; // NOT USED
		pChInfo->pitch[1]       = 0; // NOT USED
		pChInfo->pitch[2]       = 0; // NOT USED
		pChInfo->scanFormat     = SYSTEM_SF_PROGRESSIVE;

		ipcBitsOutHostPrm->maxQueueDepth[i] = MAX_BUFFERING_QUEUE_LEN_PER_CH_7500;
		ipcBitsOutHostPrm->chMaxReqBufSize[i] = (pChInfo->width * pChInfo->height);
		ipcBitsOutHostPrm->totalBitStreamBufferSize [i] = (ipcBitsOutHostPrm->chMaxReqBufSize[i] * BIT_BUF_LENGTH_LIMIT_FACTOR_HD_7500);
	}
	ipcBitsOutHostPrm->baseCreateParams.noNotifyMode   = FALSE;
	ipcBitsOutHostPrm->baseCreateParams.notifyNextLink = TRUE;
	ipcBitsOutHostPrm->baseCreateParams.numOutQue      = 1;
	ipcBitsOutHostPrm->inQueInfo.numCh                 = g_dev.decode_channel_num;
}

Void multich_hddvr_set_declink_prms_7500(DecLink_CreateParams *decPrm)
{
	int i;

	gVdecModuleContext.vdecConfig.numChn = g_dev.decode_channel_num;
	for (i=0; i<gVdecModuleContext.vdecConfig.numChn; i++)
	{
		decPrm->chCreateParams[i].format                 = IVIDEO_H264HP;
		decPrm->chCreateParams[i].profile                = IH264VDEC_PROFILE_ANY;
		decPrm->chCreateParams[i].processCallLevel       = VDEC_FRAMELEVELPROCESSCALL;
		decPrm->chCreateParams[i].targetMaxWidth         = 1920;
		decPrm->chCreateParams[i].targetMaxHeight        = 1080;
		decPrm->chCreateParams[i].numBufPerCh            = 6;
		decPrm->chCreateParams[i].tilerEnable            = TILER_ENABLE_DECODE_7500;
		decPrm->chCreateParams[i].defaultDynamicParams.targetFrameRate = gVdecModuleContext.vdecConfig.decChannelParams[i].dynamicParam.frameRate;
		decPrm->chCreateParams[i].defaultDynamicParams.targetBitRate   = gVdecModuleContext.vdecConfig.decChannelParams[i].dynamicParam.targetBitRate;
	}
}


Void multich_hddvr_set_swms_prm_7500(SwMsLink_CreateParams *swMsPrm, UInt32 swMsIdx)
{
	UInt32 devId, maxOutRes;

	swMsPrm->numSwMsInst = 1;

	if (swMsIdx == 1)
	{
		swMsPrm->swMsInstId[0] = SYSTEM_SW_MS_SC_INST_DEI_SC_NO_DEI_7500;
		//swMsPrm->includeVipScInDrvPath = TRUE;

		maxOutRes  = VSYS_STD_1080P_30;
		devId      = VDIS_DEV_HDCOMP;
	}
	else
	{
		swMsPrm->swMsInstId[0] = SYSTEM_SW_MS_SC_INST_SC5_7500;

		maxOutRes  = VSYS_STD_1080P_30;
		devId      = VDIS_DEV_HDMI;
	}

	swMsPrm->maxOutRes                   = maxOutRes;
	swMsPrm->initOutRes                  = maxOutRes;//gVdisModuleContext.vdisConfig.deviceParams[devId].resolution;
	swMsPrm->lineSkipMode                = FALSE;
	swMsPrm->enableLayoutGridDraw        = gVdisModuleContext.vdisConfig.enableLayoutGridDraw;
	swMsPrm->maxInputQueLen              = SYSTEM_SW_MS_DEFAULT_INPUT_QUE_LEN + 6;
	swMsPrm->numOutBuf                   = NUM_BUFS_PER_CH_SWMS_7500;
	swMsPrm->enableOuputDup              = TRUE;
	swMsPrm->enableProcessTieWithDisplay = TRUE;
	swMsPrm->outDataFormat               = SYSTEM_DF_YUV422I_YUYV;
	swMsPrm->outputBufModified           = TRUE;

	multich_hddvr_set_swms_default_layout(swMsPrm, devId);
}

Void multich_hddvr_set_display_prms_7500(DisplayLink_CreateParams *displayPrm,
		UInt32 maxOutRes)
{
	displayPrm->displayRes = maxOutRes;
}

Void multich_hddvr_set_avsync_vidque_prm_7500(Avsync_SynchConfigParams *queCfg,
		Int chnum,
		UInt32 avsStartChNum,
		UInt32 avsEndChNum)
{
	queCfg->chNum = chnum;
	queCfg->audioPresent = FALSE;
	if ((queCfg->chNum >= avsStartChNum)
			&&
			(queCfg->chNum <= avsEndChNum)
			&&
			(gVsysModuleContext.vsysConfig.enableAVsync))
	{
		queCfg->avsyncEnable = FALSE;
	}
	else
	{
		queCfg->avsyncEnable = FALSE;
	}
	queCfg->clkAdjustPolicy.refClkType = AVSYNC_REFCLKADJUST_NONE;
	queCfg->playTimerStartTimeout = 0;
	queCfg->playStartMode = AVSYNC_PLAYBACK_START_MODE_WAITSYNCH;
	queCfg->ptsInitMode   = AVSYNC_PTS_INIT_MODE_APP;
	queCfg->clkAdjustPolicy.clkAdjustLead = AVSYNC_VIDEO_TIMEBASESHIFT_MAX_LEAD_MS;
	queCfg->clkAdjustPolicy.clkAdjustLag = AVSYNC_VIDEO_TIMEBASESHIFT_MAX_LAG_MS;
	queCfg->vidSynchPolicy.playMaxLag    = 200;
}

Void multich_hddvr_set_avsync_prm_7500(AvsyncLink_LinkSynchConfigParams *avsyncPrm,
		UInt32 swMsIdx,
		UInt32 prevLinkID,
		UInt32 prevLinkQueId)
{
	System_LinkInfo                   swmsInLinkInfo;
	Int i;
	Int32 status;

	if (0 == swMsIdx)
	{
		Vdis_getAvsyncConfig(VDIS_DEV_HDMI,avsyncPrm);
		avsyncPrm->displayLinkID        = Vdis_getDisplayId(VDIS_DEV_HDMI);
		avsyncPrm->videoSynchLinkID = gVdisModuleContext.swMsId[Vdis_getDisplayContextIndex(VDIS_DEV_HDMI)];
	}
	else
	{
		Vdis_getAvsyncConfig(VDIS_DEV_HDCOMP,avsyncPrm);
		avsyncPrm->displayLinkID        = Vdis_getDisplayId(VDIS_DEV_HDCOMP);
		avsyncPrm->videoSynchLinkID = gVdisModuleContext.swMsId[Vdis_getDisplayContextIndex(VDIS_DEV_HDCOMP)];
	}
	System_linkGetInfo(prevLinkID,&swmsInLinkInfo);
	OSA_assert(swmsInLinkInfo.numQue > prevLinkQueId);

	avsyncPrm->numCh            = swmsInLinkInfo.queInfo[prevLinkQueId].numCh;
	avsyncPrm->syncMasterChnum = AVSYNC_INVALID_CHNUM;
	for (i = 0; i < avsyncPrm->numCh;i++)
	{
		multich_hddvr_set_avsync_vidque_prm_7500(&avsyncPrm->queCfg[i],
				i,
				gVcapModuleContext.vcapConfig.numChn,
				(gVcapModuleContext.vcapConfig.numChn + (gVdecModuleContext.vdecConfig.numChn - 1)));
	}
	if (0 == swMsIdx)
	{
		Vdis_setAvsyncConfig(VDIS_DEV_HDMI,avsyncPrm);
	}
	else
	{
		Vdis_setAvsyncConfig(VDIS_DEV_HDCOMP,avsyncPrm);
	}

	status = Avsync_configSyncConfigInfo(avsyncPrm);
	OSA_assert(status == 0);

}



Void multich_hddvr_set_swms_default_layout_7500(SwMsLink_CreateParams *swMsPrm, UInt32 devId)
{
	SwMsLink_LayoutPrm *layoutInfo;
	SwMsLink_LayoutWinInfo *winInfo;
	UInt32 outWidth, outHeight, winId, widthAlign, heightAlign;
	UInt32 rowMax,colMax,row,col;

	MultiCh_swMsGetOutSize(swMsPrm->initOutRes, &outWidth, &outHeight);

	widthAlign = 8;
	heightAlign = 1;

	if(devId>=VDIS_DEV_MAX)
		devId = VDIS_DEV_HDMI;

	rowMax = 3;
	colMax = 3;

	layoutInfo = &swMsPrm->layoutPrm;

	/* init to known default */
	memset(layoutInfo, 0, sizeof(*layoutInfo));

	layoutInfo->onlyCh2WinMapChanged = FALSE;
	layoutInfo->outputFPS            = 30;
	layoutInfo->numWin               = rowMax * colMax;

	for(row=0; row<rowMax; row++)
	{
		for(col=0; col<colMax; col++)
		{
			winId = row*colMax+col;

			winInfo = &layoutInfo->winInfo[winId];

			winInfo->width  = VsysUtils_floor(outWidth/colMax    , widthAlign );
			winInfo->height = VsysUtils_floor(outHeight/rowMax   , heightAlign);
			winInfo->startX = VsysUtils_floor(winInfo->width*col , widthAlign );
			winInfo->startY = VsysUtils_floor(winInfo->height*row, heightAlign);

			if (col == colMax - 1) /* the last col */
			{
				winInfo->width = outWidth - winInfo->width * (colMax - 1);
			}

			if(devId == VDIS_DEV_SD)
			{
				winInfo->channelNum = winId; /* show live 540p res CHs */
			}
			else
			{
				winInfo->channelNum = winId + MAX_NUM_CAPTURE_CHANNELS_7500; /* show live 540p res CHs */
				winInfo->channelNum = winId;
			}

			winInfo->bypass = FALSE;
		}
	}
	printf("swMsId: %d, numWin: %d\n", 0, g_swms[0].layoutPrm.numWin);
	//*
	int i;
	for(i = 0; i < g_swms[0].layoutPrm.numWin; i++) {
		printf("\t\tbypass: %d, channelNum: %d, x: %d, y: %d, width: %d, height: %d\n"
			, g_swms[0].layoutPrm.winInfo[i].bypass
			, g_swms[0].layoutPrm.winInfo[i].channelNum
			, g_swms[0].layoutPrm.winInfo[i].startX
			, g_swms[0].layoutPrm.winInfo[i].startY
			, g_swms[0].layoutPrm.winInfo[i].width
			, g_swms[0].layoutPrm.winInfo[i].height
			);
	}
	//*/
}



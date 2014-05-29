#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "common.h"
#include "decode.h"
#include "encode.h"
#include "split.h"
#include "../common_sdk.h"
#include "mcfw/interfaces/common_def/ti_vsys_common_def.h"



#include "system_def.h"

#include "../common_sdk.h"
#include "../common/system_def.h"

#include "../encode/vcap_venc_vdis.h"
#include "../decode/vdec_vdis.h"
#include "../osd/osd.h"

extern void SwmsLayoutInit();
extern int vga_output_patch(int resolution);
int SystemInit();
int SystemUninit(void);
void MultiCh_createHdDvr1();
void MultiCh_deleteHdDvr1();
void MultiCh_create5300A();
void MultiCh_delete5300A();

extern VdecVdis_Config      gVdecVdis_config;
char g_productID[32] = "";
DEVICE_CAPABILITY g_dev = {0 };

extern Int32 Debug_eventHandler(UInt32 eventId, Ptr pPrm, Ptr appData);

// 调用这个空函数确保constructor和destructor被执行
void SystemNull()
{
}

static void exception_action(int signo, siginfo_t* info, void* ct)
{
	SystemUninit();
}

static Int64 get_current_time_to_msec(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return ((Int64)tv.tv_sec*1000 + tv.tv_usec/1000);
}

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <errno.h>

int test_fb_dev(const char *fbdev)
{
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	char *fbp ;
	int x = 0, y = 0; 
	long int location = 0;

	/* open /dev/fb0 */
	fbfd = open(fbdev, O_RDWR);
	if (fbfd <= 0) {
		printf("Error: cannot open framebuffer device, errno: %d:\n", errno);
		perror("");
		return -1;
	}
	printf("The framebuffer device was opened successfully.\n");   
	/* 得到framebuffer设备的固定屏幕信息 */
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
		return -2;
	}
	printf("The framebuffer fixed information.\n smem_len=%d, line_length=%d\n",finfo.smem_len,finfo.line_length);
	/* 得到可变屏幕信息 */
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable information.\n");
		return -2;
	}
	printf("The framebuffer variable information.\n xres=%d, yres=%d,xoffset=%d, yoffset=%d,bits_per_pixel=%d\n"
		,vinfo.xres,vinfo.yres,vinfo.xoffset,vinfo.yoffset,vinfo.bits_per_pixel);
	/* 将映射的显存的大小 */
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	/* 将显存映射到用户空间 */
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	//虚拟内存映射，负责把文件的内容映射到进程的虚拟内存空间，就可以对这段内存的访问和修改（mmap返回的那个指针的位置），来实现对文件的读取和修改，而不再调用read，write等操作。
	if ((int)fbp == -1) {
		printf("Error: failed to map framebuffer device to memory.\n");
		return -4;
	}
	printf("The framebuffer device was mapped to memory successfully.\n");

	for (y = 200; y < 700 && y < vinfo.yres; y++) {
		for (x =200; x < 600 && x < vinfo.xres; x++) {
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
			/* 简单处理,假定是32位或16位 565模式*/
			if(vinfo.bits_per_pixel ==32){
				*(fbp + location) = 100; //some blue
				*(fbp + location + 1) = 15+(x-200)/2; //a little green 
				*(fbp + location + 2) = 200-(y-400)/5; // a lot of red 
				*(fbp + location + 3) = 0; //no transparency

			} else {//assume 16 bpp
				unsigned short b = 10; 
				unsigned short g = (x-200)/6; //a little green 
				unsigned short r = 31-(y-400)/16; //a lot of red
				unsigned short t = r<<11 | g<<5 | b; 
				*((unsigned short *)(fbp + location)) = t;       
			}
		}
	}
	
#if 0
	getchar();
	munmap(fbp, screensize);
	printf("The framebuffer device was munmapped to memory successfully.\n");
	close(fbfd);
	printf("The framebuffer device was closed successfully.\n");
#endif

	return 0;
}

void set_graphics2_node()
{
	VSYS_PARAMS_S sysInfo;
	Vsys_getContext(&sysInfo);

	FILE *fp = NULL;
	fp = fopen("/sys/devices/platform/vpss/graphics2/nodes", "wb");
	if(fp!=NULL)
	{
		OSA_printf("Opened file Graphics-2 File\n");
		fputs("1:sd", fp);
		fclose(fp);
	}
	else
	{
		printf("????????????????? Could Not open  Graphics-2 File\n");
	}
}
extern AlgLink_OsdChWinParams g_osdChParam[ALG_LINK_OSD_MAX_CH];


Void Venc_params_init2(VENC_PARAMS_S * pContext)
{

    UInt16 chId;
    VENC_CHN_DYNAMIC_PARAM_S *pDynPrm;
    VENC_CHN_PARAMS_S *pChPrm;

    memset(pContext, 0, sizeof(VENC_PARAMS_S));
    pContext->numPrimaryChn = 0;
    pContext->numSecondaryChn = 0;
    pContext->numTertiaryChn  = 0;
    printf("VENC_CHN_MAX : %d\n", VENC_CHN_MAX);
    /*Baseline profile 给323用*/
    for (chId=0; chId < VENC_CHN_MAX; chId++) {
        if(chId == 9){
            
            pContext->h264Profile[chId] = VENC_CHN_BASELINE_PROFILE; //VENC_CHN_HIGH_PROFILE;
        }else {
            pContext->h264Profile[chId] = VENC_CHN_HIGH_PROFILE;
        }
        pChPrm  = &pContext->encChannelParams[chId];
        pDynPrm = &pChPrm->dynamicParam;

        pChPrm->enableAnalyticinfo = 0;
        pChPrm->enableWaterMarking = 0;
        pChPrm->enableSVCExtensionFlag = VENC_IH264_SVC_EXTENSION_FLAG_DISABLE;
        pChPrm->encodingPreset     = VENC_XDM_USER_DEFINED;
        pChPrm->maxBitRate         = -1;
        pChPrm->rcType             = VENC_RATE_CTRL_VBR;
        pChPrm->numTemporalLayer   = VENC_TEMPORAL_LAYERS_1;

        pDynPrm->frameRate          = 30; // NOT USED
        pDynPrm->targetBitRate      = 2000 * 1000;
        pDynPrm->intraFrameInterval = 30;
        pDynPrm->interFrameInterval = 1;
        pDynPrm->inputFrameRate     = pDynPrm->frameRate;
        pDynPrm->rcAlg              = pChPrm->rcType; // MUST be same as pChPrm->rcType
        pDynPrm->qpMin              = 10;
        pDynPrm->qpMax              = 40;
        pDynPrm->qpInit             = -1; // SHOULD BE SET to -1 ALWAYS
        pDynPrm->vbrDuration        =  8;
        pDynPrm->vbrSensitivity     =  0;

        if( chId >= VENC_PRIMARY_CHANNELS)
        {
            /* secondary channels have different defaults */
            pDynPrm->targetBitRate = 500 * 1000;
        }
        if( chId >= VENC_PRIMARY_CHANNELS * 3)
        {
            /* secondary channels have different defaults */
            pDynPrm->targetBitRate = 125 * 1000;
        }

    }

    return;
}


int SystemInit()
{
	printf("============SystemInit entry.>>>>>>>>>>>>\n");

    unsigned short  osdFormat[ALG_LINK_OSD_MAX_CH];
    
	VSYS_PARAMS_S vsysParams;
	VCAP_PARAMS_S vcapParams;
	VENC_PARAMS_S vencParams;
	VDEC_PARAMS_S vdecParams;
	VDIS_PARAMS_S vdisParams;

	Vsys_params_init(&vsysParams);
	Vcap_params_init(&vcapParams);
	Venc_params_init2(&vencParams);
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

	//sleep(3);
	//printf("=================================\n");
#if 0
	grpx_fb_init(GRPX_FORMAT_RGB565);
#endif
#if 0
	set_graphics2_node();
	test_fb_dev("/dev/fb0");
	test_fb_dev("/dev/fb2");
#endif
	//printf("=================================\n");
	//sleep(3);

	// 系统需要的设置
	UInt64 wallTimeBase;
	wallTimeBase = get_current_time_to_msec();
	wallTimeBase = 0;
	Vdis_setWallTimeBase(wallTimeBase);
	//printf("before Vsys_configureDisplay()\n"); getchar();
	//system("echo 0 > /sys/devices/platform/vpss/graphics0/enabled");
	//system("echo 0 > /sys/devices/platform/vpss/graphics1/enabled");
	//system("echo 0 > /sys/devices/platform/vpss/graphics2/enabled");
	Vsys_configureDisplay();

	//system("echo 1 > /sys/devices/platform/vpss/graphics0/enabled");
	//system("echo 1 > /sys/devices/platform/vpss/graphics1/enabled");
	//system("echo 1 > /sys/devices/platform/vpss/graphics2/enabled");
	//printf("after  Vsys_configureDisplay()\n"); getchar();
	Vsys_registerEventHandler(Debug_eventHandler, NULL);
	VcapVenc_bitsWriteCreate();		// 获取码流的线程
	SwmsLayoutInit();			// 初始化的拼接模式
	printf("============System constructor leave<<<<<<<<<<<<\n");

	// usercase
	if(0 == strcmp(g_productID, "ESVR-6800A") || 0 == strcmp(g_productID, "ESVR-8800D") || 0 == strcmp(g_productID, "ESVR-8800DI")) {
		MultiCh_createHdDvr1();
		//__OsdInit();
		__OsdInit_onechannel();


        
        int chId = 0;

        for(chId = 0; chId < ALG_LINK_OSD_MAX_CH; chId++)
            osdFormat[chId] = SYSTEM_DF_YUV420SP_UV;
        Demo_osdInit(10, osdFormat);
        for(chId = 0; chId < 10; chId++)
        {
            vcapParams.channelParams[chId].dynamicParams.osdChWinPrm = &g_osdChParam[chId];
            /* Initailize osdLink with created and set win params */
            Vcap_setDynamicParamChn(chId, &vcapParams.channelParams[chId].dynamicParams, VCAP_OSDWINPRM);
            
            
        }
    } else if(0 == strcmp(g_productID, "ECT-7200")){
        MultiCh_createHdDvr_7500();
        
        int chId = 0;

        for(chId = 0; chId < ALG_LINK_OSD_MAX_CH; chId++)
            osdFormat[chId] = SYSTEM_DF_YUV420SP_UV;
        Demo_osdInit(2, osdFormat);
        for(chId = 0; chId < 2; chId++)
        {
            vcapParams.channelParams[chId].dynamicParams.osdChWinPrm = &g_osdChParam[chId];
            /* Initailize osdLink with created and set win params */
            Vcap_setDynamicParamChn(chId, &vcapParams.channelParams[chId].dynamicParams, VCAP_OSDWINPRM);
            
            
        }
	} else if(0 == strcmp(g_productID, "ESVR-6000")) {
	} else if(0 == strcmp(g_productID, "ESVR-7000")) {
	} else if(0 == strcmp(g_productID, "ESVR-7200")) {
	} else if(0 == strcmp(g_productID, "ESVR-8200")) {
	} else if(0 == strcmp(g_productID, "EHD-5300A")) {
		MultiCh_create5300A();
	} else {
		printf("WARNING: invalid productID, forget set?\n");
	}

	// Start components in reverse order
	Vdis_start();
	if(g_dev.vi_channel_num + g_dev.decode_channel_num + g_dev.swms_encode_num > 0) {
		Vcap_start();
		Venc_start();
	}
	if(g_dev.decode_channel_num > 0) {
		Vdec_start();
	}
	Audio_systemInit();

	//sleep(1);
	printf("%s call finish.\n", __func__);
	return 0;
}

int SystemUninit()
{
	printf("SystemUninit() entry.\n");
	Audio_systemDeInit();
	//AudioInStop(0);

	// 停止各个模块
	if(g_dev.decode_channel_num > 0) {
		Vdec_stop();
	}
	if(g_dev.vi_channel_num + g_dev.decode_channel_num + g_dev.swms_encode_num > 0) {
		Venc_stop();
		Vcap_stop();
	}
	Vdis_stop();

	printf("============System destructor entry>>>>>>>>>>>>\n");
	printf("delete all links\n");
	if(0 == strcmp(g_productID, "ESVR-6800A") || 0 == strcmp(g_productID, "ESVR-8800D") || 0 == strcmp(g_productID, "ESVR-8800DI")) {
        Demo_osdDeinit();
		__OsdUninit();
		MultiCh_deleteHdDvr1();
    } else if(0 == strcmp(g_productID, "ECT-7200")){
        Demo_osdDeinit();
        MultiCh_deleteHdDvr_7500();
	} else if(0 == strcmp(g_productID, "ESVR-6000")) {
	} else if(0 == strcmp(g_productID, "ESVR-7000")) {
	} else if(0 == strcmp(g_productID, "ESVR-7200")) {
	} else if(0 == strcmp(g_productID, "ESVR-8200")) {
	} else if(0 == strcmp(g_productID, "EHD-5300A")) {
		MultiCh_delete5300A();
	} else {
		printf("WARNING: invalid productID, forget set?\n");
	}

	printf("delete stream read/write thread\n");
	VcapVenc_bitsWriteDelete();
	Vsys_deConfigureDisplay();

	printf("mcfw exit api call\n");
	Vdis_exit();
	Vdec_exit();
	Venc_exit();
	Vcap_exit();
	Vsys_exit();
	sleep(1);
	printf("============System destructor leave<<<<<<<<<<<<\n");
	return 0;
}

Int32 Vsys_printDetailedStatistics();
Int32 Vsys_printBufferStatistics();

//extern int encode_static[];
//extern int decode_static[];
int SystemOutputVpssVicpInfo(int flags)
{
	int i;

	printf("====================Vsys_printDetailedStatistics=======================\n");
	Vsys_printDetailedStatistics();
	printf("====================Vsys_printBufferStatistics=========================\n");
	Vsys_printBufferStatistics();
	printf("====================encode/decode statistics===========================\n");
	printf("==================================end==================================\n");
	printf("encode: ");
	for(i = 0; i < 32; i++) {
		//printf("%d-%d, ", i, encode_static[i]);
	}
	printf("\n");
	printf("decode: ");
	for(i = 0; i < 32; i++) {
		//printf("%d-%d, ", i, decode_static[i]);
	}
	printf("\n");
	return 0;
}

int SystemSetProductID(const char *productID)
{
	printf("Version: %s, SystemSetProductID: %s\n", LIB_CAPTURE_VERSION, productID);
	strncpy(g_productID, productID, sizeof(g_productID) - 1);

	// 每一种产品定义一个link的usercase
	if(0 == strcmp(g_productID, "ESVR-8800D")) {
		g_dev.vi_channel_num		= 4;		// multich_hddvr_connect_links()中select，必须是4路不能更改
		g_dev.decode_channel_num	= 1;
		g_dev.stream_type		= 2;		// 和links流程有关
		g_dev.swms_encode_num		= 1;		// 更改对应的link流程需要修改
		g_dev.swms_display_num		= 2;
		g_dev.swms_support_hdmi		= 1;
		g_dev.swms_support_ypbpr	= 0;
		g_dev.swms_support_dvo2		= 0;
		g_dev.swms_support_sd		= 1;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;

		g_dev.osd_win_max_width		= 480;
		g_dev.osd_win_max_height	= 64;
		g_dev.osd_win_max_window	= 2;
		g_dev.ao_device_num		    = 2;
		g_dev.ao_channel_num		    = 2;
		g_dev.ai_channel_num		= 1;
	}else if(0 == strcmp(g_productID, "ESVR-8800DI")) {
		g_dev.vi_channel_num		= 4;		// multich_hddvr_connect_links()中select，必须是4路不能更改
		g_dev.decode_channel_num	= 1;
		g_dev.stream_type		= 2;		// 和links流程有关
		g_dev.swms_encode_num		= 1;		// 更改对应的link流程需要修改
		g_dev.swms_display_num		= 2;
		g_dev.swms_support_hdmi		= 1;
		g_dev.swms_support_ypbpr	= 0;
		g_dev.swms_support_dvo2		= 0;
		g_dev.swms_support_sd		= 1;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;

		g_dev.osd_win_max_width		= 480;
		g_dev.osd_win_max_height	= 64;
		g_dev.osd_win_max_window	= 2;
		g_dev.ao_device_num		    = 2;
		g_dev.ao_channel_num		    = 2;
		g_dev.ai_channel_num		= 1;
	} else if(0 == strcmp(g_productID, "ESVR-6800A")) {
		g_dev.vi_channel_num		= 4;		// multich_hddvr_connect_links()中select，必须是4路不能更改
		g_dev.decode_channel_num	= 2;
		g_dev.stream_type		= 2;		// 和links流程有关
		g_dev.swms_encode_num		= 1;		// 更改对应的link流程需要修改
		g_dev.swms_display_num		= 2;
		g_dev.swms_support_hdmi		= 1;
		g_dev.swms_support_ypbpr	= 0;
		g_dev.swms_support_dvo2		= 0;
		g_dev.swms_support_sd		= 1;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;

		g_dev.osd_win_max_width		= 480;
		g_dev.osd_win_max_height	= 64;
		g_dev.osd_win_max_window	= 2;
		g_dev.ao_device_num		= 1;
		g_dev.ai_channel_num		= 1;
	} else if(0 == strcmp(g_productID, "ECT-7200")){
        g_dev.vi_channel_num		= 2;		// multich_hddvr_connect_links()中select，必须是4路不能更改
		g_dev.decode_channel_num	= 2;
		g_dev.stream_type		= 1;		// 和links流程有关
		g_dev.swms_encode_num		= 0;		// 更改对应的link流程需要修改
		g_dev.swms_display_num		= 2;
		g_dev.swms_support_hdmi		= 1;
		g_dev.swms_support_ypbpr	= 0;
		g_dev.swms_support_dvo2		= 1;
		g_dev.swms_support_sd		= 0;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;

		g_dev.osd_win_max_width		= 480;
		g_dev.osd_win_max_height	= 64;
		g_dev.osd_win_max_window	= 2;
		g_dev.ao_device_num		= 2;
		g_dev.ai_channel_num		= 2;
    }else if(0 == strcmp(g_productID, "ESVR-6000")) {
		g_dev.vi_channel_num		= 0;
		g_dev.decode_channel_num	= 6;
		g_dev.swms_encode_num		= 0;
		g_dev.stream_type		= 0;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;
		g_dev.osd_win_max_width		= 320;
		g_dev.osd_win_max_height	= 32;
		g_dev.ao_device_num		= 1;
	} else if(0 == strcmp(g_productID, "ESVR-7000")) {
		g_dev.vi_channel_num		= 1;
		g_dev.decode_channel_num	= 5;
		g_dev.swms_encode_num		= 1;
		g_dev.stream_type		= 1;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;
		g_dev.osd_win_max_width		= 320;
		g_dev.osd_win_max_height	= 32;
		g_dev.ao_device_num		= 1;
	} else if(0 == strcmp(g_productID, "ESVR-7200")) {
	} else if(0 == strcmp(g_productID, "ESVR-8200")) {
	} else if(0 == strcmp(g_productID, "EHD-5300A")) {
		// 产品规格参考老李邮件: 2013年9月30日(星期一) 下午4:56
		g_dev.vi_channel_num		= 0;
		g_dev.decode_channel_num	= 6;
		g_dev.swms_encode_num		= 0;
		g_dev.swms_display_num		= 3;
		g_dev.swms_support_hdmi		= 1;
		g_dev.swms_support_ypbpr	= 1;
		g_dev.swms_support_dvo2		= 0;
		g_dev.swms_support_sd		= 1;
		g_dev.stream_type		= 0;

		g_dev.decode_max_width		= 1920;
		g_dev.decode_max_height		= 1080;
		g_dev.osd_win_max_width		= 320;
		g_dev.osd_win_max_height	= 32;
		g_dev.ao_device_num		= 1;
	} else {
		printf("FETAL ERROR: how do u set the f**K product type?\n");
		while(1) sleep(100);
	}

	// 解码通道配置表
	int i;
	gVdecVdis_config.numChannels = g_dev.decode_channel_num;
	for(i = 0; i < g_dev.decode_channel_num; i++) {
		gVdecVdis_config.res[i].width = g_dev.decode_max_width;
		gVdecVdis_config.res[i].height = g_dev.decode_max_height;
		gVdecVdis_config.chBufSize[i] = g_dev.decode_max_width * g_dev.decode_max_height;
	}

	
	printf("decode_channel_num: %d, vi_channel_num: %d, swms_encode_num: %d, ao_device_num : %d, ai_channel_num : %d, stream_type : %d\n"
		, g_dev.decode_channel_num, g_dev.vi_channel_num, g_dev.swms_encode_num, g_dev.ao_device_num, g_dev.ai_channel_num, g_dev.stream_type);

	printf("swms_encode_num : %d, swms_display_num : %d, swms_support_hdmi : %d, swms_support_ypbpr : %d, swms_support_dvo2 : %d, swms_support_sd : %d\n"
		, g_dev.swms_encode_num, g_dev.swms_display_num, g_dev.swms_support_hdmi, g_dev.swms_support_ypbpr, g_dev.swms_support_dvo2, g_dev.swms_support_sd);
	printf("decode_max_width : %d, decode_max_height : %d, osd_win_max_width : %d, osd_win_max_height : %d, osd_win_max_window : %d\n"
		, g_dev.decode_max_width, g_dev.decode_max_height, g_dev.osd_win_max_width, g_dev.osd_win_max_height, g_dev.osd_win_max_window);

	return 0;
}

int SystemGetProductCapability(DEVICE_CAPABILITY *cap)
{
	memcpy(cap, &g_dev, sizeof(DEVICE_CAPABILITY));
	return 0;
}

int SystemGetVersion(char *version)
{
	const char *str = LIB_CAPTURE_VERSION;
	if(version)
		strcpy(version, str);

	return 0;
}

SYSTEM_DEBUG_INFO g_debug_info = {0 };
int SystemGetDebug(SYSTEM_DEBUG_INFO *info)
{
	memset(info, 0x0, sizeof(SYSTEM_DEBUG_INFO));
	memcpy(info, &g_debug_info, sizeof(SYSTEM_DEBUG_INFO));
	return 0;
}

void printTimeString()
{
	time_t tm1;
	time(&tm1);
	struct tm *tm2 = gmtime(&tm1);
	printf("%d-%d-%d %d:%d:%d", tm2->tm_year + 1900, tm2->tm_mon, tm2->tm_mday, tm2->tm_hour, tm2->tm_min, tm2->tm_sec);
}


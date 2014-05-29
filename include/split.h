/*



   .' ~ ~`".
   / |	  \
   |   \__.-, (_,
   \ /`   9 `\ /
   ,_	 )| 9 .   |`
   \'.	'.\  ,_/  /
   _\ \.--.'.___.' `'.
   -' _`	a  \.--, .'   |
   ""` \ a K  ; ,-'\ _.;_
   '.__,. (__.'`-._ )
   (_/\ '-.     /_
   ;-._)-._/ _)
   /	   `` \
   '-._______.-'
   |_ |_ |
   |__|__/
   .-"'-'|--|
   '.___,_|""|
   \__/



 */
#ifndef __ETAH_SPLIT_H_20130402_
#define __ETAH_SPLIT_H_20130402_
#include "common.h"

/* @{ */

/**
  \brief Possible Video Standards - NTSC, PAL, CIF, etc
  \����sdk����Ա��������ݽṹ!!!
 */
typedef enum
{
	ETAH_DISPLAY_STD_NTSC = 0u,
	/**< 720x480 30FPS interlaced NTSC standard. */
	ETAH_DISPLAY_STD_PAL,
	/**< 720x576 30FPS interlaced PAL standard. */

	ETAH_DISPLAY_STD_480I,
	/**< 720x480 30FPS interlaced SD standard. */
	ETAH_DISPLAY_STD_576I,
	/**< 720x576 30FPS interlaced SD standard. */

	ETAH_DISPLAY_STD_CIF,
	/**< Interlaced, 360x120 per field NTSC, 360x144 per field PAL. */
	ETAH_DISPLAY_STD_HALF_D1,
	/**< Interlaced, 360x240 per field NTSC, 360x288 per field PAL. */
	ETAH_DISPLAY_STD_D1,
	/**< Interlaced, 720x240 per field NTSC, 720x288 per field PAL. */

	ETAH_DISPLAY_STD_480P,
	/**< 720x480 60FPS progressive ED standard. */
	ETAH_DISPLAY_STD_576P,
	/**< 720x576 60FPS progressive ED standard. */

	ETAH_DISPLAY_STD_720P_60,
	/**< 1280x720 60FPS progressive HD standard. */
	ETAH_DISPLAY_STD_720P_50,
	/**< 1280x720 50FPS progressive HD standard. */

	ETAH_DISPLAY_STD_1080I_60,
	/**< 1920x1080 30FPS interlaced HD standard. */
	ETAH_DISPLAY_STD_1080I_50,
	/**< 1920x1080 50FPS interlaced HD standard. */

	ETAH_DISPLAY_STD_1080P_60,
	/**< 1920x1080 60FPS progressive HD standard. */
	ETAH_DISPLAY_STD_1080P_50,
	/**< 1920x1080 50FPS progressive HD standard. */

	ETAH_DISPLAY_STD_1080P_24,
	/**< 1920x1080 24FPS progressive HD standard. */
	ETAH_DISPLAY_STD_1080P_30,
	/**< 1920x1080 30FPS progressive HD standard. */

	ETAH_DISPLAY_STD_VGA_60,
	/**< 640x480 60FPS VESA standard. */
	ETAH_DISPLAY_STD_VGA_72,
	/**< 640x480 72FPS VESA standard. */
	ETAH_DISPLAY_STD_VGA_75,
	/**< 640x480 75FPS VESA standard. */
	ETAH_DISPLAY_STD_VGA_85,
	/**< 640x480 85FPS VESA standard. */

	ETAH_DISPLAY_STD_SVGA_60,
	/**< 800x600 60FPS VESA standard. */
	ETAH_DISPLAY_STD_SVGA_72,
	/**< 800x600 72FPS VESA standard. */
	ETAH_DISPLAY_STD_SVGA_75,
	/**< 800x600 75FPS VESA standard. */
	ETAH_DISPLAY_STD_SVGA_85,
	/**< 800x600 85FPS VESA standard. */

	ETAH_DISPLAY_STD_XGA_60,
	/**< 1024x768 60FPS VESA standard. */
	ETAH_DISPLAY_STD_XGA_70,
	/**< 1024x768 72FPS VESA standard. */
	ETAH_DISPLAY_STD_XGA_75,
	/**< 1024x768 75FPS VESA standard. */
	ETAH_DISPLAY_STD_XGA_85,
	/**< 1024x768 85FPS VESA standard. */

	ETAH_DISPLAY_STD_WXGA_60,
	/**< 1280x768 60FPS VESA standard. */
	ETAH_DISPLAY_STD_WXGA_75,
	/**< 1280x768 75FPS VESA standard. */
	ETAH_DISPLAY_STD_WXGA_85,
	/**< 1280x768 85FPS VESA standard. */

	ETAH_DISPLAY_STD_SXGA_60,
	/**< 1280x1024 60FPS VESA standard. */
	ETAH_DISPLAY_STD_SXGA_75,
	/**< 1280x1024 75FPS VESA standard. */
	ETAH_DISPLAY_STD_SXGA_85,
	/**< 1280x1024 85FPS VESA standard. */

	ETAH_DISPLAY_STD_SXGAP_60,
	/**< 1400x1050 60FPS VESA standard. */
	ETAH_DISPLAY_STD_SXGAP_75,
	/**< 1400x1050 75FPS VESA standard. */

	ETAH_DISPLAY_STD_UXGA_60,
	/**< 1600x1200 60FPS VESA standard. */

	ETAH_DISPLAY_STD_MUX_2CH_D1,
	/**< Interlaced, 2Ch D1, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_2CH_HALF_D1,
	/**< Interlaced, 2ch half D1, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_2CH_CIF,
	/**< Interlaced, 2ch CIF, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_4CH_D1,
	/**< Interlaced, 4Ch D1, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_4CH_CIF,
	/**< Interlaced, 4Ch CIF, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_4CH_HALF_D1,
	/**< Interlaced, 4Ch Half-D1, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_8CH_CIF,
	/**< Interlaced, 8Ch CIF, NTSC or PAL. */
	ETAH_DISPLAY_STD_MUX_8CH_HALF_D1,
	/**< Interlaced, 8Ch Half-D1, NTSC or PAL. */

	ETAH_DISPLAY_STD_AUTO_DETECT,
	/**< Auto-detect standard. Used in capture mode. */
	ETAH_DISPLAY_STD_CUSTOM,
	/**< Custom standard used when connecting to external LCD etc...
	  The video timing is provided by the application.
	  Used in display mode. */

	ETAH_DISPLAY_STD_MAX
		/**< Should be the last value of this enumeration.
		  Will be used by driver for validating the input parameters. */
} ETAH_DISPLAY_VIDEO_STANDARD_E;

typedef enum
{
	ETAH_SWMS_ID_HDMI	= 0,
	ETAH_SWMS_ID_MOSAIC,		// ����
	ETAH_SWMS_ID_SD,
	ETAH_SWMS_ID_HDCOMP,
    ETAH_SWMS_ID_DVO2,
	ETAH_SWMS_ID_MAX
} ETAH_SWMS_ID;

#ifdef __cplusplus
extern "C" {
#endif

int SplitInit(void);
int SplitUnit(void);

// compositorID: 0, 1, 2...
// ��Ƶƴ��: ������ʾ, channelNR����Ҫƴ�ӵ�·����rects����Ҫƴ��·���Ĳ�������
// ���������ͽ�������ƴ�ӷ�ʽ�ο�VIDEO_RECT���ݽṹ˵��
int SplitSetCompositorMosaic(ETAH_SWMS_ID compositorID, int channelNR, VIDEO_RECT *rects);
int SplitSetDisplayResolution(ETAH_SWMS_ID compositorID/*ETAH_VDIS_DEV dev*/, int outputResolution);

// ����: ��Ҫʹ�ýӿ�SplitSetCompositorDevice()!!!!!!
int SplitSetCompositorDevice(int compositorID, int device);

// ƴ����ʹ��
//int SplitEnable(int compositorID);
//int SplitDisable(int compositorID);


// �����ӽӿ�(��̬����������Ƶ�ֱ���)��δ������ʱ��Ҫʹ��!
int CaptureSetVideoPortStandard(int channel, int width, int height);

#ifdef __cplusplus
}
#endif

#endif

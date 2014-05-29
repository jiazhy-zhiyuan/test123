/*
 *

                   .-"      "-.
                  /            \
                 |              |
                 |,  .-.  .-.  ,|
                 | )(__/  \__)( |
                 |/     /\     \|
       (@_       (_     ^^     _)
  _     ) \_______\__|IIIIII|__/__________________________
 (_)@8@8{}<________|-\IIIIII/-|___________________________>
        )_/        \          /
       (@           `--------`


  */
#ifndef __ETAH_ENCODE_H_20130402_
#define __ETAH_ENCODE_H_20130402_
#include "common.h"

typedef enum STREAM_TYPE
{
	STREAM_TYPE_PRIMARY,
	STREAM_TYPE_SECOND
} STREAM_TYPE;

typedef enum _ENCODE_TYPE{
	ENCODE_TYPE_H264
}ENCODE_TYPE;

typedef enum _FRAME_TYPE{
	FRAME_TYPE_IFRAME,		/*I֡*/
	FRAME_TYPE_PFRAME		/*P֡*/
}FRAME_TYPE;

typedef struct _VIDEO_STREAM_PARAM{
	int chnId;
	STREAM_TYPE stream_type;	/*������,�������������*/
	ENCODE_TYPE encode_type;	/*��������,Ŀǰֻ֧��H264*/
	FRAME_TYPE frame_type;		/*֡����,��ǰ֡��I ֡����P֡*/
	void * bufVirtAddr;			/*���ݵ�ַ*/
	int filledBufSize;		/*���ݴ�С*/
	int width;			/*��Ƶ���*/
	int height;			/*��Ƶ�߶�*/
	int   timestamp;		/*ʱ��*/
	int   seqId;			/*֡���,��ʾ��ʼ����ڶ���֡��*/
}VIDEO_STREAM_PARAM;


//typedef  void * VCODEC_BITSBUF_S;

// VCODEC_BITSBUF_S��dvrrdk�л�����Ϣ�Ľṹ, ����ͨ���ţ��������ͣ�֡���ͣ�buf��ַ������timeStamp����ȣ��߶ȵ�
typedef int (*EncodeGetBuffer_Callback)(VIDEO_STREAM_PARAM *video_stream_param);					// ��ȡ�����Ļص�����


/**
    \brief Encoder Rate-control type
*/
typedef enum RC_CTRL_E_
{
    VENC_RATE_CTRL_VBR_ = 0,
    /**< [IH264_RATECONTROL_PRC] Variable Bitrate: For Local Storage*/

    VENC_RATE_CTRL_CBR_ = 1,
    /**< [IH264_RATECONTROL_PRC_LOW_DELAY]Constant Bitrate: For Video Conferencing*/

} VENC_RATE_CTRL_E_;


/**
    \brief Profile Identifier for H.264 Encoder
*/
typedef enum
{
    ETAH_VENC_CHN_BASELINE_PROFILE = 66,                     // ����
    /**< BaseLine Profile   */

    ETAH_VENC_CHN_MAIN_PROFILE     = 77,                     // ����
    /**< Main Profile       */

    ETAH_VENC_CHN_EXTENDED_PROFILE = 88,                     
    /**< Extended Profile   */

    ETAH_VENC_CHN_HIGH_PROFILE     = 100,                    // ����
    /**< High Profile       */

    ETAH_VENC_CHN_DEFAULT_PROFILE  = ETAH_VENC_CHN_HIGH_PROFILE,  
    /**< Default Profile    */

    ETAH_VENC_CHN_HIGH10_PROFILE   = 110,                    
    /**< High 10 Profile    */

    ETAH_VENC_CHN_HIGH422_PROFILE  = 122,
    /**< High 4:2:2 Profile */
    
    ETAH_VENC_CHN_SVC_BASELINE_PROFILE = 83,
    /**< SVC Baseline Profile */

    ETAH_VENC_CHN_SVC_HIGH_PROFILE      = 86
    /**< SVC High Profile */

} ETAH_VENC_CHN_H264_Profile_E;

// �������ݸ�ʽ�ṹ
typedef struct ENCODE_FORMAT
{
	int					Compression;		// ѹ����׼: h.264/mpeg4/jpeg,Ŀǰֻ��h.264����(��ʱ����)
	int					ImageSize;		// ͼ���С(��ʱ����)
	int					ImageQuality;		// ͼ������(��ʱ����)

	VENC_RATE_CTRL_E_			BitRateControl;		// ��������ģʽ
	int					GOP;			// 
	int					FrameRate;		// ����֡��
	int					BitRate;		// �ο�����ֵ
	ETAH_VENC_CHN_H264_Profile_E		algType;
	int					width;
	int					height;
} ENCODE_FORMAT;

// ϵͳʱ��ṹ
typedef struct tagSYSTEM_TIME
{
	int  year;			// ��
	int  month;			// ��
	int  day;			// ��
	int  hour;			// ʱ
	int  minute;			// ��
	int  second;			// ��
} SYSTEM_TIME;

// ���������Ӳ����ṹ
typedef struct ENCODE_TITLE_PARAM
{
	int		enable;

	int		x;
	int		y;
	unsigned short	width;
	unsigned short	height;

	unsigned char	*raster;
	int		size;
	int		alpha;		// ����: 0��100��ֵ��0��ȫ͸����100�ǲ�͸��
	int		colorkey;	// ����: 
	int		enable_colorkey;// 
}ENCODE_TITLE_PARAM;

extern ENCODE_FORMAT	g_encode_format[];

#ifdef __cplusplus
extern "C" {
#endif

// ����ͨ����ؽӿڣ�ͨ����: 0,1,2,3,4.....·������ʵ�ʲ�Ʒ����
// ������4·�������룬2·ƴ�ӵ�������ô����6·����: 0,1,2,3�Ǳ�������channel��; 4,5��ƴ�ӵ�������channel��
int EncodeInit(int ichannel, STREAM_TYPE dwType);
int EncodeUninit(int ichannel, STREAM_TYPE dwType);
int EncodeStart(int ichannel, STREAM_TYPE dwType);
int EncodeStop(int ichannel, STREAM_TYPE dwType);
int EncodeForceIFrame(int ichannel, STREAM_TYPE dwType);					//ǿ�Ʊ���������I֡
int EncodeSetFormat(int ichannel, STREAM_TYPE dwType, ENCODE_FORMAT *pFormat);			// dwType�����������ߴ�����
int EncodeSetGetBufferCallback(EncodeGetBuffer_Callback getCb);
int EncodeSetTitle(int ichannel, STREAM_TYPE dwType, int index, ENCODE_TITLE_PARAM *pParam);
int EncodeShowTime(int ichannel, STREAM_TYPE dwType, int bShowTime);
/* int EncodeSetProfile(int ichannel, STREAM_TYPE dwType, ETAH_VENC_CHN_H264_Profile_E profile); */
#ifdef __cplusplus
}
#endif

#endif


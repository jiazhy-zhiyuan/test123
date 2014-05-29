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
	FRAME_TYPE_IFRAME,		/*I帧*/
	FRAME_TYPE_PFRAME		/*P帧*/
}FRAME_TYPE;

typedef struct _VIDEO_STREAM_PARAM{
	int chnId;
	STREAM_TYPE stream_type;	/*流类型,主码流或次码流*/
	ENCODE_TYPE encode_type;	/*编码类型,目前只支持H264*/
	FRAME_TYPE frame_type;		/*帧类型,当前帧是I 帧还是P帧*/
	void * bufVirtAddr;			/*数据地址*/
	int filledBufSize;		/*数据大小*/
	int width;			/*视频宽度*/
	int height;			/*视频高度*/
	int   timestamp;		/*时戳*/
	int   seqId;			/*帧序号,表示开始编码第多少帧了*/
}VIDEO_STREAM_PARAM;


//typedef  void * VCODEC_BITSBUF_S;

// VCODEC_BITSBUF_S是dvrrdk中缓冲信息的结构, 包括通道号，码流类型，帧类型，buf地址，各种timeStamp，宽度，高度等
typedef int (*EncodeGetBuffer_Callback)(VIDEO_STREAM_PARAM *video_stream_param);					// 获取码流的回调函数


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
    ETAH_VENC_CHN_BASELINE_PROFILE = 66,                     // 常用
    /**< BaseLine Profile   */

    ETAH_VENC_CHN_MAIN_PROFILE     = 77,                     // 常用
    /**< Main Profile       */

    ETAH_VENC_CHN_EXTENDED_PROFILE = 88,                     
    /**< Extended Profile   */

    ETAH_VENC_CHN_HIGH_PROFILE     = 100,                    // 常用
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

// 捕获数据格式结构
typedef struct ENCODE_FORMAT
{
	int					Compression;		// 压缩标准: h.264/mpeg4/jpeg,目前只有h.264参数(暂时不用)
	int					ImageSize;		// 图像大小(暂时不用)
	int					ImageQuality;		// 图像质量(暂时不用)

	VENC_RATE_CTRL_E_			BitRateControl;		// 码流控制模式
	int					GOP;			// 
	int					FrameRate;		// 编码帧率
	int					BitRate;		// 参考码流值
	ETAH_VENC_CHN_H264_Profile_E		algType;
	int					width;
	int					height;
} ENCODE_FORMAT;

// 系统时间结构
typedef struct tagSYSTEM_TIME
{
	int  year;			// 年
	int  month;			// 月
	int  day;			// 日
	int  hour;			// 时
	int  minute;			// 分
	int  second;			// 秒
} SYSTEM_TIME;

// 捕获标题叠加参数结构
typedef struct ENCODE_TITLE_PARAM
{
	int		enable;

	int		x;
	int		y;
	unsigned short	width;
	unsigned short	height;

	unsigned char	*raster;
	int		size;
	int		alpha;		// 增加: 0到100的值，0是全透明，100是不透明
	int		colorkey;	// 增加: 
	int		enable_colorkey;// 
}ENCODE_TITLE_PARAM;

extern ENCODE_FORMAT	g_encode_format[];

#ifdef __cplusplus
extern "C" {
#endif

// 编码通道相关接口，通道号: 0,1,2,3,4.....路数根据实际产品定义
// 比如有4路本地输入，2路拼接导播，那么共有6路编码: 0,1,2,3是本地输入channel号; 4,5是拼接导播编码channel号
int EncodeInit(int ichannel, STREAM_TYPE dwType);
int EncodeUninit(int ichannel, STREAM_TYPE dwType);
int EncodeStart(int ichannel, STREAM_TYPE dwType);
int EncodeStop(int ichannel, STREAM_TYPE dwType);
int EncodeForceIFrame(int ichannel, STREAM_TYPE dwType);					//强制编码器产生I帧
int EncodeSetFormat(int ichannel, STREAM_TYPE dwType, ENCODE_FORMAT *pFormat);			// dwType是主码流或者次码流
int EncodeSetGetBufferCallback(EncodeGetBuffer_Callback getCb);
int EncodeSetTitle(int ichannel, STREAM_TYPE dwType, int index, ENCODE_TITLE_PARAM *pParam);
int EncodeShowTime(int ichannel, STREAM_TYPE dwType, int bShowTime);
/* int EncodeSetProfile(int ichannel, STREAM_TYPE dwType, ETAH_VENC_CHN_H264_Profile_E profile); */
#ifdef __cplusplus
}
#endif

#endif


#ifndef __ENCODE_DEF_ETAH_20130411_H_
#define __ENCODE_DEF_ETAH_20130411_H_
#include "../common/system_def.h"

typedef struct tagSTREAM_CHN_INFO
{
	int enc_chn;
	int channel;
	int dwtype;
	int frame_rate;
	int pic_width;
	int pic_height;
	int image_size;
	
	unsigned long long oldpts;			// 用于PS流的时间标记
	unsigned long long scr;				// 用于PS流的时间标记
	unsigned long long vpts;			
	unsigned long long apts;			

}STREAM_CHN_INFO;

// 视频编码通道信息结构
typedef struct tagVENC_CHN_INFO
{
	int vencChn;
	int created;						// 编码通道是否被创建
	int started;						// 编码通道是否被开启
	int enable;							// 视频编码使能
	int pic_width;						// 图象宽度
	int pic_height;						// 图象高度
	int frame_rate;						// 帧率
	int image_size;
	int venc_fd;
	int gop;							// 帧间隔
	int bitrate;
	int cbrvbr;
	int preframe;
	int cur_frame_rate;
	int frame_count;
	int error_count;
	unsigned long long oldpts;			// 用于PS流的时间标记
	unsigned long long scr;				// 用于PS流的时间标记
	pthread_t threadid;
	pthread_mutex_t lock;				// 用于防止编码设置和采集的冲突
	struct timeval oldtime;

	STREAM_CHN_INFO info;

} VENC_CHN_INFO_t;

// 音频编码信息结构
typedef struct tagAENC_CHN_INFO
{
	int HiAencChn;
	int created;						// 编码通道是否被创建
	int started;						// 编码通道是否被开启
	int regular_enable;					// 主码流中音频编码使能
	int extra_enable;					// 辅码流中音频编码使能
	pthread_t threadid;
	int Channel;
	int AiDev;
	int AiChn;
	unsigned long long oldpts;		// 用于PS流的时间标记
	unsigned long long scr;				// 用于PS流的时间标记
	pthread_mutex_t lock;
	STREAM_CHN_INFO info[2];
} AENC_CHN_INFO_t;

// 视频通道属性结构
typedef struct tagVI_CHN_INFO
{
	int binded;
	int vi_picsize;
	int vi_width;
	int vi_height;
	int vi_capsel;
	int vi_downscale;
	int vi_framerate;
	int split_picsize;
	int split_framerate;
	int venc_picsize;
	int venc_framerate;

	VENC_CHN_INFO_t venc_chn[2];				// 两个视频编码通道，主辅码流
	AENC_CHN_INFO_t aenc_chn;				// 一个音频编码通道
} VI_CHN_INFO_t;

// 设备信息结构
typedef struct tagCapture_Dev
{
	int sys_init;
	int venc_opened;					// 视频编码器是否打开，0为关闭，1为打开
	int aenc_opened;					// 音频编码器是否打开，0为关闭，1为打开

	int vstd;						// 视频制式
	int video_codec_format;					// 视频编解码格式
	int audio_codec_format;					// 音频编解码格式

	time_t basetime;					//pts的基准时间

	VI_CHN_INFO_t  vi_chn[MAX_VI_CHN];			// 视频输入通道

	pthread_mutex_t lock;
} Capture_Dev_t;

#endif


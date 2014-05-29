/*
 *
 *
 *             .======.
 *             | INRI |
 *             |      |
 *             |      |
 *    .========'      '========.
 *    |   _      xxxx      _   |
 *    |  /_;-.__ / _\  _.-;_\  |
 *    |     `-._`'`_/'`.-'     |
 *    '========.`\   /`========'
 *             | |  / |
 *             |/-.(  |
 *             |\_._\ |
 *             | \ \`;|
 *             |  > |/|
 *             | / // |
 *             | |//  |
 *             | \(\  |
 *             |  ``  |
 *             |      |
 *             |      |
 *             |      |
 *             |      |
 * \\    _  _\\| \//  |//_   _ \// _
 *^ `^`^ ^`` `^ ^` ``^^`  `^^` `^ `^
 *
 */
#ifndef __COMMON_ETAH_20130402_H_
#define __COMMON_ETAH_20130402_H_
//#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#define LIB_CAPTURE_VERSION       "LIB_CAPTURE_VERSION 1.1.1.2XXYYZZ #" __DATE__ " " __TIME__

typedef enum _COORDINATE_MODE{
	COORDINATE_MODE_RATIO,			// 按比例模式, 值是0到100
	COORDINATE_MODE_PIXEL			// 像素坐标模式
} COORDINATE_MODE;

// channelNum只用于拼接模块，是需要拼接的本地视频输入或解码码流channel号，前面是本地视频输入channel，接下来是解码码流channel
// 例如:
// 有4路本地视频输入，2路解码; 0,1,2,3是本地视频输入，4,5是解码码流
typedef struct VIDEO_RECT
{
	int		startX;
	int		startY;
	int		width;
	int		height;
	int		channelNum;		// 采集和解码通道统一编址

	int		layer;			// 有效的整形数: 数字大的显示在上层，小的显示在底层
	COORDINATE_MODE	coordinate_mode;	// 坐标模式 added by wangqiguo 2013-6-24
} VIDEO_RECT;

#include <asm/byteorder.h>
//#define le16toh(x)	__le16_to_cpu(x)
//#define be16toh(x)	__be16_to_cpu(x)
//#define le32toh(x)	__le32_to_cpu(x)
//#define be32toh(x)	__be32_to_cpu(x)

#define dpline()		do {							\
	printf("run at %s:%d-------------------\n", __func__, __LINE__);		\
	usleep(1000 * 100);								\
} while(0)

#define dpline_stop()		do {							\
		printf("run at %s:%d-------------------\n", __func__, __LINE__);	\
		getchar();								\
	} while(0)

int printfbin(void *buf_, int size);

//#define SWMS_MAX_DISPLAY_DEV		4	// 最多显示设备: hdmi, hdcomp, dvo2, sd一共4个
#define SWMS_MAX_WIN_PER_LINK		16	// 每个显示设备上最多显示路数

#ifndef VENC_PRIMARY_CHANNELS
/** Maximum Video Encode channels */
#define VENC_PRIMARY_CHANNELS   (16)
#endif

#endif


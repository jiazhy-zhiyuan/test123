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
	COORDINATE_MODE_RATIO,			// ������ģʽ, ֵ��0��100
	COORDINATE_MODE_PIXEL			// ��������ģʽ
} COORDINATE_MODE;

// channelNumֻ����ƴ��ģ�飬����Ҫƴ�ӵı�����Ƶ������������channel�ţ�ǰ���Ǳ�����Ƶ����channel���������ǽ�������channel
// ����:
// ��4·������Ƶ���룬2·����; 0,1,2,3�Ǳ�����Ƶ���룬4,5�ǽ�������
typedef struct VIDEO_RECT
{
	int		startX;
	int		startY;
	int		width;
	int		height;
	int		channelNum;		// �ɼ��ͽ���ͨ��ͳһ��ַ

	int		layer;			// ��Ч��������: ���ִ����ʾ���ϲ㣬С����ʾ�ڵײ�
	COORDINATE_MODE	coordinate_mode;	// ����ģʽ added by wangqiguo 2013-6-24
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

//#define SWMS_MAX_DISPLAY_DEV		4	// �����ʾ�豸: hdmi, hdcomp, dvo2, sdһ��4��
#define SWMS_MAX_WIN_PER_LINK		16	// ÿ����ʾ�豸�������ʾ·��

#ifndef VENC_PRIMARY_CHANNELS
/** Maximum Video Encode channels */
#define VENC_PRIMARY_CHANNELS   (16)
#endif

#endif


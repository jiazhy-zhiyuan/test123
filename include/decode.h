/*
 *
 *                (\__
 *               (\   `\__
 * (`, .------.,-'     b  |
 *  `-/          ',__,-"` 
 *   |   `;      ,  |
 *    \   ;.----/ ,/
 *     ) // /  ( ( \
 *     \ \`.`\  \ \ \
 *      `-` `"   `-`"
 *
 */
#ifndef __ETAH_DECODE_H_20130402_
#define __ETAH_DECODE_H_20130402_
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_VIDEO_DECODE_NUM		8

// ����ͨ����ؽӿڣ�����ͨ����: 0,1,2,3,4.....·������ʵ�ʲ�Ʒ����
int DecodeInit(int channel);
int DecodeUninit(int channel);
int DecodeStart(int channel);
int DecodeStop(int channel);	// ���ô˽ӿں���ͣ�������һ֡�����ϣ������Ҫ���ɺ�������Ҫ����SplitSetCompositorMosaic()�Ѹ�λ�õ�channelNum��Ϊ��Чֵ(����)

int DecodePutBuffer(int channel, void *pBuffer, int dwCount);
#ifdef __cplusplus
}
#endif

#endif


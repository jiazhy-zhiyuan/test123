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

// 解码通道相关接口，解码通道号: 0,1,2,3,4.....路数根据实际产品定义
int DecodeInit(int channel);
int DecodeUninit(int channel);
int DecodeStart(int channel);
int DecodeStop(int channel);	// 调用此接口后画面停留在最后一帧解码上，如果需要做成黑屏，需要调用SplitSetCompositorMosaic()把该位置的channelNum改为无效值(负数)

int DecodePutBuffer(int channel, void *pBuffer, int dwCount);
#ifdef __cplusplus
}
#endif

#endif


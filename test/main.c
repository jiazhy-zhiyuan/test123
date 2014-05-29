#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "encode.h"
#include "split.h"
#include "system.h"
#include "src/common_sdk.h"
#include "nipdebug.h"

int main_audio_in(int argc, char *argv[]);
int main_audio_out(int argc, char *argv[]);
int main_audio_out2(int argc, char *argv[]);
int SystemInit();
int main_encode_decode();
void display_link_test();
void encode_link_test();

__attribute__((unused)) void *debug_thread(void *arg)
{
				
	while(1) {
		int input = getchar();
		// debug

		if('d' == input) {
			printf("Vsys_printDetailedStatistics()=======================================\n");
			Vsys_printDetailedStatistics();
			printf("end.=================================================================\n");
		}
		if('b' == input) {
			printf("Vsys_printBufferStatistics()=========================================\n");
			Vsys_printBufferStatistics();
			printf("end.=================================================================\n");
		}
	}

	return ((void *)0);
}

//#include <demo.h>
Int32 Debug_eventHandler(UInt32 eventId, Ptr pPrm, Ptr appData);
extern void *test_write_decode_buffer_thread(void *arg);

int main(int argc, char *argv[])
{
	init_nipdebug(0, 0, 0, 0);

	if(argc != 2) {
		printf("usage: %s vi|de...\n", argv[1]);
		return 0;
	}

	if(0 == strcmp(argv[1], "ljz")) {
		display_link_test();
		sleep(999999);
	}

	if(0 == strcmp(argv[1], "vi")) {
		SystemSetProductID("ESVR-6800A");
		SystemInit();
		main_encode_decode();
	}

	if(0 == strcmp(argv[1], "de")) {
		SystemSetProductID("EHD-5300A");
		SystemInit();
		main_encode_decode();
	}

	if(0 == strcmp(argv[1], "test")) {
		SystemSetProductID("EHD-5300A");

		
		pthread_t tid = 0;
		int i = 0;
		//pthread_create(&tid, NULL, test_write_decode_buffer_thread, (void *)i);
		while(1) {
			printf("======================================\n");
			printf("======================================\n");
			printf("======================================\n");
			SystemInit();

			VIDEO_RECT rect[SWMS_MAX_WIN_PER_LINK] = { 0};
			// 1个大窗口
			rect[0].channelNum = 0;
			rect[0].startX = 0;
			rect[0].startY = 0;
			rect[0].width = 1920 * 4 / 4 + 0;
			rect[0].height = 1080 * 4 / 4 + 0;
			SplitSetCompositorMosaic(0, 1, rect);

			DecodeInit(0);
			DecodeStart(0);
			test_write_decode_buffer_thread(0);
			//sleep(25);	// work
			DecodeStop(0);
			DecodeUninit(0);
			SystemUninit();
			while(1) {
				char ch = getchar();
				if('a' == ch)
					break;
			}
		}
	}

	// 进入主线程
	//printf("=====================2013.4.17=========================\n");
	//pthread_t tid;
	//pthread_create(&tid, NULL, debug_thread, NULL);
	//printf("\n\n\n\npause here......\n");
	sleep(999999);
	return 0;
}


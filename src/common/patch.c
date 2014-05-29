#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include "split.h"

#define VPSS_DISPLAY3_CONTROL_BASE	0x48108000
#define VPSS_DISPLAY3_CONTROL_SIZE	1024
int vga_output_patch(int resolution)
{
	int g_fd = open("/dev/mem", O_RDWR);
	if(g_fd < 0) {
		printf("%s() open /dev/mem failed.\n", __func__);
		return -1;
	}

	unsigned long mapaddr = (unsigned long)mmap((void *)VPSS_DISPLAY3_CONTROL_BASE, (size_t)VPSS_DISPLAY3_CONTROL_SIZE
		, PROT_READ | PROT_WRITE, MAP_SHARED, g_fd, (off_t)VPSS_DISPLAY3_CONTROL_BASE);
	if(0 == mapaddr) {
		printf("%s() mmap failed.\n", __func__);
		return -2;
	}

	switch(resolution) {
		case ETAH_DISPLAY_STD_1080P_60:
		{
			printf("patch for ETAH_DISPLAY_STD_1080P_60\n");
			*(int *)(mapaddr + 0x00) = 0x44033013;
			*(int *)(mapaddr + 0x1c) = 0x00000b00;
			*(int *)(mapaddr + 0x20) = 0x00000b00;
			*(int *)(mapaddr + 0x24) = 0x00000b00;
			*(int *)(mapaddr + 0x30) = 0x2c7800b5;
			*(int *)(mapaddr + 0x38) = 0x0;
			*(int *)(mapaddr + 0x3c) = 0x2c7800c0;
			*(int *)(mapaddr + 0x54) = 0x2c7800b1;
			*(int *)(mapaddr + 0xd4) = 0x00000111;
			break;
		}
		case ETAH_DISPLAY_STD_720P_60:
		{
			printf("patch for ETAH_DISPLAY_STD_720P_60\n");
			/*
			*(int *)(mapaddr + 0x00) = 0x44033013;
			*(int *)(mapaddr + 0x1c) = 0x00000b00;
			*(int *)(mapaddr + 0x20) = 0x00000b00;
			*(int *)(mapaddr + 0x24) = 0x00000b00;
			*(int *)(mapaddr + 0x30) = 0x2c7800b5;
			*(int *)(mapaddr + 0x38) = 0x0;
			*(int *)(mapaddr + 0x3c) = 0x2c7800c0;
			*(int *)(mapaddr + 0x54) = 0x2c7800b1;
			*(int *)(mapaddr + 0xd4) = 0x00000111;
			*/
			break;
		}
		case ETAH_DISPLAY_STD_XGA_60:
		{
			printf("patch for ETAH_DISPLAY_STD_XGA_60\n");
			/*
			*(int *)(mapaddr + 0x00) = 0x44033013;
			*(int *)(mapaddr + 0x1c) = 0x00000b00;
			*(int *)(mapaddr + 0x20) = 0x00000b00;
			*(int *)(mapaddr + 0x24) = 0x00000b00;
			*(int *)(mapaddr + 0x30) = 0x2c7800b5;
			*(int *)(mapaddr + 0x38) = 0x0;
			*(int *)(mapaddr + 0x3c) = 0x2c7800c0;
			*(int *)(mapaddr + 0x54) = 0x2c7800b1;
			*(int *)(mapaddr + 0xd4) = 0x00000111;
			*/

			// by lizhongming
			*(int *)(mapaddr + 0x00) = 0x44033011;
			*(int *)(mapaddr + 0x30) = 0x2c7880bd;
			*(int *)(mapaddr + 0x1c) = 0x00000800;
			*(int *)(mapaddr + 0x20) = 0x00000800;
			*(int *)(mapaddr + 0x24) = 0x00000800;
			break;
		}
		default:
		{
			break;
		}
	}

	munmap((void *)mapaddr, (size_t)VPSS_DISPLAY3_CONTROL_SIZE);
	close(g_fd);
	printf("set vga output finish.\n");
	return 0;
}


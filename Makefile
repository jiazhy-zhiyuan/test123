CROSS_COMPILE	=arm-arago-linux-gnueabi-
TOP_DIR_BASE    = $(shell basename `/bin/pwd`)
DEBUG_FLAG	= -pg -g

#-----------------------------------------------------------------------------------------
#WARNING: do *NOT* modify below
ALSA_INC = $(DVRRDK_PATH)/ti_tools/linux_devkit/arm-none-linux-gnueabi/usr/include
ALSA_LIB = $(DVRRDK_PATH)/ti_tools/linux_devkit/arm-none-linux-gnueabi/usr/lib
INCLUDE := -I`pwd`
INCLUDE += -I`pwd`/include
INCLUDE += -I`pwd`/src/demo
INCLUDE += -I$(ALSA_INC)
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/interfaces
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/interfaces/common_def
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/interfaces/link_api
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/src_linux/osa/inc
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/src_linux/mcfw_api/usecases
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/src_linux/devices/inc
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/src_linux/devices/sii9022a/inc
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/src_linux/devices/thsfilters/inc
INCLUDE += -I$(DVRRDK_PATH)/dvr_rdk/mcfw/src_linux/devices/tvp5158/inc
#for usecases(link api call)
INCLUDE += -I$(DVRRDK_PATH)/ti_tools/ipc/ipc_1_24_03_32/packages
INCLUDE += -I$(DVRRDK_PATH)/ti_tools/syslink/syslink_2_20_02_20/packages
INCLUDE += -I$(DVRRDK_PATH)/ti_tools/xdais/xdais_7_22_00_03/packages
INCLUDE += -I$(DVRRDK_PATH)/ti_tools/codecs/REL.500.V.H264AVC.E.IVAHD.02.00.04.01/500.V.H264AVC.E.IVAHD.02.00/IVAHD_001/Inc
INCLUDE += -I$(DVRRDK_PATH)/ti_tools/codecs/REL.500.V.H264AVC.E.IVAHD.02.00.06.00/500.V.H264AVC.E.IVAHD.02.00/IVAHD_001/Inc
INCLUDE += -I$(DVRRDK_PATH)/ti_tools/codecs/REL.500.V.H264AVC.D.HP.IVAHD.02.00.08.00/500.V.H264AVC.D.HP.IVAHD.02.00/IVAHD_001/Inc

LIBS := -L$(ALSA_LIB)
LIBS += $(wildcard lib/*.a) ./lib/libcapture.a ./lib/librtmp.a ./lib/libnipdebug.a
LIBS += -lpthread -lm -ldl -lrt
LIBS += $(DVRRDK_PATH)/dvr_rdk/lib/ti816x-evm/dvr_rdk_mcfw_api.a
LIBS += $(DVRRDK_PATH)/dvr_rdk/lib/ti816x-evm/dvr_rdk_link_api.a
LIBS += $(DVRRDK_PATH)/dvr_rdk/lib/ti816x-evm/dvr_rdk_common_utils.a
LIBS += $(DVRRDK_PATH)/dvr_rdk/lib/ti816x-evm/dvr_rdk_osa.a
LIBS += $(DVRRDK_PATH)/ti_tools/syslink/syslink_2_20_02_20/packages/ti/syslink/lib/syslink.a_release
LIBS += $(DVRRDK_PATH)/ti_tools/cgt_a8/arago/linux-devkit/arm-arago-linux-gnueabi/usr/lib/libasound.so.2
#LIBS += $(DVRRDK_PATH)/ti_tools/linux_devkit/arm-none-linux-gnueabi/usr/lib/libasound.so.2
LIBS += $(DVRRDK_PATH)/ti_tools/rpe/remote-processor-execute/lib/lib/a8/debug/rpe.av5T

CXXFLAGS	:= -DTI_816X_BUILD -Werror -fno-omit-frame-pointer
SRCS		:= $(wildcard src/*/*.c)
LIB_OBJS	:= $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRCS)))
SRCS2		:= $(wildcard test/*.c)
MAIN_OBJS	:= $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRCS2)))
OUT_LIB		:= lib/libcapture.a
SHARE_LIB	:= lib/libcapture.so
OUT_EXE		:= bin/encode_demo

all: OUT_LIB  SHARE_LIB
	$(CROSS_COMPILE)g++ $(DEBUG_FLAG) -o $(OUT_EXE) $(MAIN_OBJS) $(LIBS)
	#@make --no-print-directory clean
	#cp lib/libcapture.a ~/source/rtmptest/libcapture.a -f
	#find ./ -name "*.o"| xargs rm -f
	@echo -e "\033[1;33m>>>>>>  link test $(OUT_EXE) at `date +%F\ %H:%M:%S` \033[0m" >&2
	@date

OUT_LIB: $(LIB_OBJS) $(MAIN_OBJS)
	$(CROSS_COMPILE)ar r $(OUT_LIB) $(LIB_OBJS)
	@echo -e "\033[1;35m>>>>>>  archive all source code at `date +%F\ %H:%M:%S` \033[0m" >&2

SHARE_LIB: $(LIB_OBJS) $(MAIN_OBJS)
	$(CROSS_COMPILE)gcc $(DEBUG_FLAG) -shared -fPIC -o $(SHARE_LIB) $(LIB_OBJS)
	@echo -e "\033[1;35m>>>>>>  archive all source code at `date +%F\ %H:%M:%S` \033[0m" >&2	

clean:
	@echo $(DVRRDK_PATH)
	find ./ -name "*.o"| xargs rm -f
	rm -f $(OUT_LIB)

%.o: %.c
	@echo -e "\033[1;32m>>>>>>  compiling: $<\033[0m" >&2
	$(CROSS_COMPILE)gcc $(DEBUG_FLAG) $(INCLUDE) $(CXXFLAGS) -c -o $@ $<

%.o: %.cpp
	@echo -e "\033[1;32m>>>>>>  compiling: $<\033[0m" >&2
	$(CROSS_COMPILE)g++ $(DEBUG_FLAG) $(INCLUDE) $(CXXFLAGS) -c -o $@ $<

bak:
	@(cd ../; tar jcf ./libcapture.`date +%F_%H.%M.%S`.tar.bz2 $(TOP_DIR_BASE))
	@echo -e "\033[1;32m>>>>>>  backup source code at `date +%F\ %H:%M:%S` \033[0m" >&2


TARGET = PSPProject
OBJS = main.o \
gfx.o

CFLAGS = 
LIBS += -lm -lstdc++
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)

#PSP
BUILD_PRX = 1
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSPProject

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
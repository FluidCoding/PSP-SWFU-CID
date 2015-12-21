TARGET = SWFUCD
OBJS = main.o address.o

# Define to build this as a prx (instead of a static elf)
BUILD_PRX=1
PSP_FW_VERSION = 300

USE_KERNEL_LIBS = 1
USE_KERNEL_LIBC = 1

INCDIR = 
CFLAGS = -O2 -G0 -w -msingle-float -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpsppower -lpspchnnlsv -lpsputility -lpspdebug -lpspge_driver -lpspgum -lpspgu -lm -lpspchnnlsv -lpspge_driver -lpspwlan -lpspumd
LDFLAGS = -nostdlib  -nodefaultlibs -g

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

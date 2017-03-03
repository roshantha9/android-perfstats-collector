NDK = $(HOME)/android-ndk-r13b
TOOLCHAIN = $(ANDROID_NDK_TOOLCHAIN_ROOT)
SYSROOT = $(TOOLCHAIN)/sysroot
GCC = $(TOOLCHAIN)/bin/arm-linux-androideabi-gcc
STRIP = $(TOOLCHAIN)/bin/arm-linux-androideabi-strip
CFLAGS = -march=armv7-a -mfloat-abi=softfp -I$(SYSROOT)/usr/include -std=c99 -pedantic -Wall \
		-Wpointer-arith -Wcast-qual -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization  \
		-Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wsign-conversion  \
		-Wstrict-overflow=5 -Wswitch-default -Wundef -Wstrict-prototypes  \
		-Wmissing-prototypes -Wmissing-declarations -Wmissing-field-initializers -Wmissing-declarations
LDFLAGS = -Wl,--fix-cortex-a8 -L$(SYSROOT)/usr/lib

DEPS = android-perfstats-collector.h collect-gpucpu.h collect-mem.h locations.h common.h debug.h

all: android-perfstats-collector

android-perfstats-collector: android-perfstats-collector.o collect-gpucpu.o collect-mem.o debug.o
	$(GCC) $(LDFLAGS) -o $@ android-perfstats-collector.o collect-gpucpu.o collect-mem.o debug.o
	$(STRIP) -s $@

%.o: %.c $(DEPS)
	$(GCC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f android-perfstats-collector *.o .*.un~

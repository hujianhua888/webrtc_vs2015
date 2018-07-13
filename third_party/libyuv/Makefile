V ?= @
SRC=src
ANDROID_PROJECT_PATH=../../prj_android
PREFIX=$(PWD)/$(MMAKE_ARCHNAME)

usage:
	@echo "usage: make all|android|x86|clean"
	@echo "cwd = $(PWD)"

all: clean android x86

android:
	ndk-build -B NDK_PROJECT_PATH=$(ANDROID_PROJECT_PATH) APP_BUILD_SCRIPT=./Android.mk 
	
build:
	$(V)make -C $(SRC) -f linux.mk

x86:build 
	$(V)if [ ! -d "$(PREFIX)/lib" ]; then mkdir -p $(PREFIX)/lib; fi
	
	$(V)cp -f $(SRC)/libyuv.a $(PREFIX)/lib/
	$(V)cp -a $(SRC)/include/*.*  $(PREFIX)/include/*.*
clean:
	$(V)make -C $(SRC) -f linux.mk clean

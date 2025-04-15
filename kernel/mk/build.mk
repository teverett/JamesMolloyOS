
# detect build platform
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
include mk/gcc-i386-darwin.mk
else
include mk/gcc-i386-linux.mk
endif
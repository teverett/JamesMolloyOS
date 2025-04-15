

# detect build platform
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
GCC=x86_64-elf-gcc
else
CC=gcc
endif

GCC = gcc
CFLAGS =
TARGET = initrd_generator
SRC = initrd_generator.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(GCC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

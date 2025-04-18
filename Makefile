
# detect build platform
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
QEMU=qemu-system-i386
else
QEMU=qemu-system-i386
endif

all: kernel/bin/kernel.elf initrd.img

kernel/bin/kernel.elf:
	make -C kernel clean
	make -C kernel

initrd_generator/initrd_generator: initrd_generator/initrd_generator.c
	make -C initrd_generator clean
	make -C initrd_generator

initrd.img: initrd_generator/initrd_generator 
	initrd_generator/initrd_generator fs/recuerdo.txt recuerdo.txt  fs/abc.txt abc.txt

run: kernel/bin/kernel.elf initrd.img
	$(QEMU) -kernel kernel/bin/kernel.elf -initrd initrd.img

debug: kernel/bin/kernel.elf initrd.img
	$(QEMU) -kernel kernel/bin/kernel.elf -initrd initrd.img -gdb tcp::1234 -S

clean:
	rm -f initrd.img
	rm -f initrd_generator/initrd_generator
	rm -f kernel/bin/kernel.elf



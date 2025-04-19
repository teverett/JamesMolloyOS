
GCC=gcc
LD=ld
CFLAGS=-c -ggdb3 -Wextra -Wno-sign-compare -Wno-implicit-function-declaration -fno-builtin -fno-stack-protector -m32 -nostdlib -nostdinc
LDFLAGS=-T src/link.ld -m elf_i386
NASM=nasm
ASFLAGS=-felf

# objcopy
OBJCOPY=objcopy
OBJCOPYFLAGS=-O binary

# objdump
OBJDUMP=objdump
OBJDUMPFLAGS=

# strip
STRIP=strip
STRIPFLAGS=

# ar
AR=ar
ARFLAGS=-crs

#qemu
QEMU=qemu-system-i386

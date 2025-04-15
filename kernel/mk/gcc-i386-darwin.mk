# requires 'brew install x86_64-elf-gcc'

GCC=i686-elf-gcc
LD=i686-elf-ld
CFLAGS=-c -ggdb3 -Wextra -Wno-sign-compare -Wno-implicit-function-declaration -fno-builtin -fno-stack-protector -m32 -nostdlib -nostdinc -std=gnu99

LDFLAGS=-T src/link.ld -m elf_i386
NASM=nasm
ASFLAGS=-felf

# objcopy
OBJCOPY=i686-elf-objcopy
OBJCOPYFLAGS=-O binary

# strip
STRIP=i686-elf-strip
STRIPFLAGS=

# ar
AR=i686-elf-ar
ARFLAGS=-crs

# qemu
QEMU=qemu-system-i686


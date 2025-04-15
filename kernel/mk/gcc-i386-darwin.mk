# requires 'brew install x86_64-elf-gcc'

GCC=x86_64-elf-gcc
LD=x86_64-elf-ld
CFLAGS=-c -ggdb3 -Wextra -Wno-sign-compare -Wno-implicit-function-declaration -fno-builtin -fno-stack-protector -m32 -nostdlib -nostdinc -std=gnu99

LDFLAGS=-T src/link.ld -m elf_i386
NASM=nasm
ASFLAGS=-felf

# objcopy
OBJCOPY=x86_64-elf-objcopy
OBJCOPYFLAGS=-O binary

# strip
STRIP=x86_64-elf-strip
STRIPFLAGS=

# ar
AR=x86_64-elf-ar
ARFLAGS=-crs

# qemu
QEMU=qemu-system-x86_64


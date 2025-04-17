
include mk/build.mk

BUILD_DIR = bin
SOURCE_DIR = src
INCLUDE_DIR= include

CSOURCE := $(wildcard $(SOURCE_DIR)/*.c)
ASOURCE := $(wildcard $(SOURCE_DIR)/*.asm)

_COBJECT := $(patsubst %.c,%.o, $(CSOURCE))
_AOBJECT := $(patsubst %.asm,%.o, $(ASOURCE))
AOBJECT = $(addprefix $(BUILD_DIR)/, $(notdir $(_AOBJECT)))
COBJECT = $(addprefix $(BUILD_DIR)/, $(notdir $(_COBJECT)))

all: bindir kernel.elf

# link all of the objects
kernel.elf: $(AOBJECT) $(COBJECT)
	$(LD) $(LDFLAGS) $(AOBJECT) $(COBJECT) -L. -Map $(BUILD_DIR)/kernel.map -o $(BUILD_DIR)/kernel.elf
	$(OBJDUMP) -S $(BUILD_DIR)/kernel.elf > $(BUILD_DIR)/kernel.elf.dump


# build c files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(GCC) -c $< -o $@ $(CFLAGS) -I $(INCLUDE_DIR)

# build asm files (Assembly)
.asm.o:
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(NASM) $(ASFLAGS) $< -o $@

bindir:
	mkdir -p $(BUILD_DIR)

run: kernel.elf
	$(QEMU) -kernel $(BUILD_DIR)/kernel.elf
	
clean:
	rm -rf $(BUILD_DIR)


	
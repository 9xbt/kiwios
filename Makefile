# binary locations
ASM = /usr/bin/nasm
CC = /usr/bin/gcc
LD = /usr/bin/ld

# grub version
GRUB = grub
# sources
SRC = SRC
ASM_SRC = src/kernel/i386/asm
KERNEL_SRC = src/kernel
# objects
BIN = bin
OBJ = obj
CONFIG = config
# flags
ASM_FLAGS = -f elf32
CC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-implicit-function-declaration -Wno-int-conversion -nostdlib

all: clean prepare asmbuild cbuild link grubsetup qemu

prepare:
	mkdir -p $(BIN)/boot/grub
	mkdir -p $(OBJ)

asmbuild:
	@printf "[ Assembling... ]\n"
	$(ASM) -f elf32 -o $(OBJ)/entry.o $(ASM_SRC)/entry.s
	$(ASM) -f elf32 -o $(OBJ)/exception.o $(ASM_SRC)/exception.s
	$(ASM) -f elf32 -o $(OBJ)/irq.o $(ASM_SRC)/irq.s
	$(ASM) -f elf32 -o $(OBJ)/gdt.o $(ASM_SRC)/gdt.s
	$(ASM) -f elf32 -o $(OBJ)/idt.o $(ASM_SRC)/idt.s

cbuild:
	@printf "[ Compiling... ]\n"
	$(CC) -m32 -c -I include $(KERNEL_SRC)/kernel.c -o $(OBJ)/kernel.o $(CC_FLAGS)

link:
	@printf "[ Linking... ]\n"
	$(LD) -m elf_i386 -T $(CONFIG)/linker.ld $(OBJ)/kernel.o $(OBJ)/entry.o $(OBJ)/exception.o $(OBJ)/irq.o $(OBJ)/gdt.o $(OBJ)/idt.o -o $(BIN)/boot/kiwios.elf -nostdlib

grubsetup:
	@printf "[ Checking if ELF is multiboot-able... ]\n"
	$(GRUB)-file --is-x86-multiboot $(BIN)/boot/kiwios.elf
	@printf "(Setting up GRUB...)\n"
	cp $(CONFIG)/grub.cfg $(BIN)/boot/grub/grub.cfg
	$(GRUB)-mkrescue -o kiwios.iso $(BIN)/

qemu:
	qemu-system-x86_64 -cdrom kiwios.iso -serial stdio

clean:
	rm -rf $(BIN)
	rm -f $(OBJ)/*.o

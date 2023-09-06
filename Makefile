# assembler
ASM = /usr/bin/nasm
# compiler
CC = /usr/bin/gcc
# linker
LD = /usr/bin/ld
# grub iso creator
GRUB = /usr/bin/grub-mkrescue
# sources
SRC = src
ASM_SRC = src/i386/asm
# objects
BIN = bin
OBJ = obj
CONFIG = config
# flags
ASM_FLAGS = -f elf32
CC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-implicit-function-declaration

all:
	mkdir -p $(BIN)/boot/grub
	mkdir -p $(OBJ)

	@printf "[ Assembling... ]\n"
	$(ASM) -f elf32 -o $(OBJ)/entry.o $(ASM_SRC)/entry.s
	$(ASM) -f elf32 -o $(OBJ)/exception.o $(ASM_SRC)/exception.s
	$(ASM) -f elf32 -o $(OBJ)/irq.o $(ASM_SRC)/irq.s
	$(ASM) -f elf32 -o $(OBJ)/gdt.o $(ASM_SRC)/gdt.s
	$(ASM) -f elf32 -o $(OBJ)/idt.o $(ASM_SRC)/idt.s
	@printf "[ Compiling... ]\n"
	$(CC) -m32 -c $(SRC)/kernel.c -o $(OBJ)/kernel.o $(CC_FLAGS)
	@printf "[ Linking... ]\n"
	$(LD) -m elf_i386 -T $(CONFIG)/linker.ld $(OBJ)/kernel.o $(OBJ)/entry.o $(OBJ)/exception.o $(OBJ)/irq.o $(OBJ)/gdt.o $(OBJ)/idt.o -o $(BIN)/boot/kiwios.elf -nostdlib
	@printf "[ Checking... ]\n"
	grub-file --is-x86-multiboot $(BIN)/boot/kiwios.elf
	cp $(CONFIG)/grub.cfg $(BIN)/boot/grub/grub.cfg
	grub-mkrescue -o kiwios.iso $(BIN)/
	qemu-system-x86_64 -cdrom kiwios.iso

clean:
	rm -rf $(BIN)
	rm -f $(OBJ)/*.o
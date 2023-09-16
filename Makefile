# assembler
ASM = /usr/bin/nasm
# compiler
CC = /usr/bin/gcc
# linker
LD = /usr/bin/ld
# grub version
GRUB = grub
# sources
SRC = src
ASM_SRC = src/i386/asm
# objects
BIN = bin
OBJ = obj
CONFIG = config
INCLUDE = ../include
# flags
ASM_FLAGS = -f elf32
CC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -I$(INCLUDE) -Wextra -Wno-int-conversion -Wno-unused-function -nostdlib
LD_FLAGS = -m elf_i386 -nostdlib -z noexecstack -T

all: build run

build:
	clear
	mkdir -p $(BIN)/boot/grub
	mkdir -p $(OBJ)

	@printf "[ Assembling... ]\n"
	@$(ASM) -f elf32 -o $(OBJ)/entry.o $(ASM_SRC)/entry.s
	@$(ASM) -f elf32 -o $(OBJ)/exception.o $(ASM_SRC)/exception.s
	@$(ASM) -f elf32 -o $(OBJ)/irq.o $(ASM_SRC)/irq.s
	@$(ASM) -f elf32 -o $(OBJ)/gdt.o $(ASM_SRC)/gdt.s
	@$(ASM) -f elf32 -o $(OBJ)/idt.o $(ASM_SRC)/idt.s
	@printf "[ Compiling... ]\n"
	@$(CC) -m32 -c -I include $(SRC)/kernel.c -o $(OBJ)/kernel.o $(CC_FLAGS)
	@printf "[ Linking... ]\n"
	@$(LD) $(LD_FLAGS) $(CONFIG)/linker.ld $(OBJ)/kernel.o $(OBJ)/entry.o $(OBJ)/exception.o $(OBJ)/irq.o $(OBJ)/gdt.o $(OBJ)/idt.o -o $(BIN)/boot/kiwios.elf
	@printf "[ Checking... ]\n"
	@$(GRUB)-file --is-x86-multiboot $(BIN)/boot/kiwios.elf
	@printf "[ Finalizing... ]\n"
	@cp $(CONFIG)/grub.cfg $(BIN)/boot/grub/grub.cfg
	@$(GRUB)-mkrescue -o kiwios.iso $(BIN)/

run:
	qemu-system-x86_64 -cdrom kiwios.iso -serial stdio

clean:
	rm -rf $(BIN)
	rm -f $(OBJ)/*.o
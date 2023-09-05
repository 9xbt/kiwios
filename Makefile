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
ASM_SRC = src/asm
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

	$(ASM) -f elf32 -o $(OBJ)/boot.o $(SRC)/boot.asm
	$(ASM) -f elf32 -o $(OBJ)/exception.o $(ASM_SRC)/exception.asm
	$(ASM) -f elf32 -o $(OBJ)/irq.o $(ASM_SRC)/irq.asm
	$(ASM) -f elf32 -o $(OBJ)/load_gdt.o $(ASM_SRC)/load_gdt.asm
	$(ASM) -f elf32 -o $(OBJ)/load_idt.o $(ASM_SRC)/load_idt.asm
	$(CC) -m32 -c $(SRC)/kernel.c -o $(OBJ)/kernel.o $(CC_FLAGS)
	$(LD) -m elf_i386 -T $(CONFIG)/linker.ld $(OBJ)/kernel.o $(OBJ)/boot.o $(OBJ)/exception.o $(OBJ)/irq.o $(OBJ)/load_gdt.o $(OBJ)/load_idt.o -o $(BIN)/boot/kiwios.elf -nostdlib
	grub-file --is-x86-multiboot $(BIN)/boot/kiwios.elf
	cp $(CONFIG)/grub.cfg $(BIN)/boot/grub/grub.cfg
	grub-mkrescue -o kiwios.iso $(BIN)/
	qemu-system-x86_64 -cdrom kiwios.iso

clean:
	rm -rf $(BIN)
	rm -f $(OBJ)/*.o
all: clean build run

run:
	qemu-system-x86_64 -cdrom ../out/kiwios.iso

build:
	mkdir -p ../bin/boot/grub
	mkdir ../out/

	nasm -f elf32 -o ../out/boot.o boot.asm

	gcc -m32 -c kernel.c -o ../out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-implicit-function-declaration

	ld -m elf_i386 -T linker.ld ../out/kernel.o ../out/boot.o -o ../bin/boot/kiwios.elf -nostdlib

	grub-file --is-x86-multiboot ../bin/boot/kiwios.elf

	cp grub.cfg ../bin/boot/grub/grub.cfg

	grub-mkrescue -o ../out/kiwios.iso ../bin

clean:
	rm -r ../bin
	rm -r ../out
/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#pragma once

#include <sys/hw/io.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER 0xB8000

static void vga_init(unsigned const char color) {
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2)
    {
        *(char*)(VGA_BUFFER + i) = 0x00;
        *(char*)(VGA_BUFFER + i + 1) = color;
    }
}

static void vga_putchar(int x, int y, const char c, const char color) {
	*(char*)((VGA_BUFFER + y * VGA_WIDTH + x) * 2) = c;
	*(char*)((VGA_BUFFER + y * VGA_WIDTH + x + 1) * 2) = color;
}

static void vga_enablecursor()
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 14);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

static void vga_movecursor(int x, int y)
{
	unsigned short int pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

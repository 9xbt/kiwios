#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER 0xB8000

void vga_init(unsigned const char color);

void vga_putchar(int x, int y, const char c, const char color);

void vga_enablecursor(void);

void vga_movecursor(int x, int y);

#include "port.h"
#include "../src/i386/vga.c"

#endif
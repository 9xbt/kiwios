/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER 0xB8000

void vga_init(unsigned const char color);
void vga_putchar(int x, int y, const char c, const char color);
void vga_enablecursor();
void vga_movecursor(int x, int y);

#include <sys/hw/io.h>
#include "vga.c"

#endif
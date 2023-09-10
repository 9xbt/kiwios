/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VGA_H
#define VGA_H

#include "port.h"
#include "../utils/logger.h"
#include "../terminal.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_init(unsigned const char color) {
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2)
    {
        *(char*)(0xB8000 + i) = 0x00;
        *(char*)(0xB8000 + i + 1) = color;
    }

	vga_enablecursor();
}

void vga_enablecursor(void)
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 14);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void vga_movecursor(int x, int y)
{
	unsigned short int pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

#endif
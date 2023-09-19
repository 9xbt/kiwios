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

#ifndef REBOOT_H
#define REBOOT_H

#include "inttypes.h"
#include "../../i386/port.h"

#define KBRD_INTRFC 0x64
#define KBRD_BIT_KDATA 0
#define KBRD_BIT_UDATA 1
 
#define KBRD_IO 0x60
#define KBRD_RESET 0xFE
 
#define bit(n) (1<<(n))

#define check_flag(flags, n) ((flags) & bit(n))
 
void cmd_reboot()
{
    uint8_t temp;
    asm volatile ("cli");
 
    do
    {
        temp = inb(KBRD_INTRFC);
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
        {
            inb(KBRD_IO);
        }
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
 
    outb(KBRD_INTRFC, KBRD_RESET);

loop:
    asm volatile ("hlt");
    goto loop;
}

#endif

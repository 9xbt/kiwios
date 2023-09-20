/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef REBOOT_H
#define REBOOT_H

#include <inttypes.h>
#include <sys/hw/io.h>

#define KBRD_INTRFC 0x64
#define KBRD_BIT_KDATA 0
#define KBRD_BIT_UDATA 1
 
#define KBRD_IO 0x60
#define KBRD_RESET 0xFE
 
#define bit(n) (1<<(n))

#define check_flag(flags, n) ((flags) & bit(n))
 
static void cmd_reboot()
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

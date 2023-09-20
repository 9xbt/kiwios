/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef PIC_H
#define PIC_H

#define PIC1            0x20       // IO base address for master PIC
#define PIC2            0xA0       // IO base address for slave PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)   // Master data
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)   // Slave data

#define PIC_EOI         0x20       // End of interrupt

#define ICW1            0x11       // Interrupt control command word PIC for initialization
#define ICW4_8086       0x01       // 8086/88 (MCS-80/85) mode

void pic_init();
void pic_eoi(uint8_t irq);

#include <inttypes.h>
#include <sys/tables/isr.h>
#include <sys/tables/idt.h>
#include <sys/hw/io.h>
#include "pic.c"

#endif

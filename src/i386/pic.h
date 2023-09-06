/**
 * 8259 Programmable Interrupt Controller(8259 PIC) setup
 */

#ifndef _8259_PIC_H
#define _8259_PIC_H

#include <inttypes.h>
#include "isr.h"
#include "idt.h"
#include "port.h"

/* for more, see https://wiki.osdev.org/8259_PIC */
#define PIC1            0x20  /* IO base address for master PIC */
#define PIC2            0xA0  /* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)    /* master data */
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)    /* slave data */

#define PIC_EOI         0x20   /* end of interrupt */

#define ICW1            0x11    /* interrupt control command word PIC for initialization */
#define ICW4_8086       0x01    /* 8086/88 (MCS-80/85) mode */

/**
 * initialize 8259 PIC with default IRQ's defined in isr.h
 */
void pic_init() {
    uint8_t a1, a2;

    // save mask registers
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // send commands to pic to initialize both master & slave
    outb(PIC1_COMMAND, ICW1);
    outb(PIC2_COMMAND, ICW1);

    // map vector offset of all default IRQ's from 0x20 to 0x27 in master(ICW2)
    outb(PIC1_DATA, 0x20);
    // map vector offset of all default IRQ's from 0x28 to 0x2F in slave(ICW2)
    outb(PIC2_DATA, 0x28);

    // ICW3: tell master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC1_DATA, 4);
    // ICW3: tell slave PIC its cascade identity (0000 0010)
    outb(PIC2_DATA, 2);

    // ICW4, set x86 mode
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // restore the mask registers
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

/**
 * send end of interrupt command to PIC 8259
 */
void pic_eoi(uint8_t irq) {
    if(irq >= 0x28)
        outb(PIC2, PIC_EOI);
    outb(PIC1, PIC_EOI);
}

#endif

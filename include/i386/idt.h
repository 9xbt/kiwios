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

#ifndef IDT_H
#define IDT_H

#include "inttypes.h"
#include "idt.h"
#include "isr.h"
#include "pic.h"
#include "../logger.h"

#define NO_IDT_DESCRIPTORS     256

typedef struct {
    uint16_t base_low;               // Lower 16 bits 0-15 of the address to jump to when this interrupt fires
    uint16_t segment_selector;       // Code segment selector in GDT
    uint8_t zero;                    // Unused
    uint8_t type;                    // Types trap, interrupt gates
    uint16_t base_high;              // Upper 16 bits 16-31 of the address to jump to
} __attribute__((packed)) IDT;

typedef struct {
    uint16_t limit;                  // Limit size of all IDT segments
    uint32_t base_address;           // Base address of the first IDT segment
} __attribute__((packed)) IDT_PTR;

// Load the IDT
extern void load_idt(uint32_t idt_ptr);

IDT g_idt[NO_IDT_DESCRIPTORS];
IDT_PTR g_idt_ptr;

// Fill IDT entries
static void idt_set_entry(int index, uint32_t base, uint16_t seg_sel, uint8_t flags) {
    IDT *this = &g_idt[index];

    this->base_low = base & 0xFFFF;
    this->segment_selector = seg_sel;
    this->zero = 0;
    this->type = flags | 0x60;
    this->base_high = (base >> 16) & 0xFFFF;
}

// External exception voids
extern void exception_0();
extern void exception_1();
extern void exception_2();
extern void exception_3();
extern void exception_4();
extern void exception_5();
extern void exception_6();
extern void exception_7();
extern void exception_8();
extern void exception_9();
extern void exception_10();
extern void exception_11();
extern void exception_12();
extern void exception_13();
extern void exception_14();
extern void exception_15();
extern void exception_16();
extern void exception_17();
extern void exception_18();
extern void exception_19();
extern void exception_20();
extern void exception_21();
extern void exception_22();
extern void exception_23();
extern void exception_24();
extern void exception_25();
extern void exception_26();
extern void exception_27();
extern void exception_28();
extern void exception_29();
extern void exception_30();
extern void exception_31();
extern void exception_128();

// External IRQ voids
extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();

// Initialize the IDT
void idt_init() {
    g_idt_ptr.base_address = g_idt;
    g_idt_ptr.limit = sizeof(g_idt) - 1;
    pic_init();

    idt_set_entry(0, exception_0, 0x08, 0x8E);
    idt_set_entry(1, exception_1, 0x08, 0x8E);
    idt_set_entry(2, exception_2, 0x08, 0x8E);
    idt_set_entry(3, exception_3, 0x08, 0x8E);
    idt_set_entry(4, exception_4, 0x08, 0x8E);
    idt_set_entry(5, exception_5, 0x08, 0x8E);
    idt_set_entry(6, exception_6, 0x08, 0x8E);
    idt_set_entry(7, exception_7, 0x08, 0x8E);
    idt_set_entry(8, exception_8, 0x08, 0x8E);
    idt_set_entry(9, exception_9, 0x08, 0x8E);
    idt_set_entry(10, exception_10, 0x08, 0x8E);
    idt_set_entry(11, exception_11, 0x08, 0x8E);
    idt_set_entry(12, exception_12, 0x08, 0x8E);
    idt_set_entry(13, exception_13, 0x08, 0x8E);
    idt_set_entry(14, exception_14, 0x08, 0x8E);
    idt_set_entry(15, exception_15, 0x08, 0x8E);
    idt_set_entry(16, exception_16, 0x08, 0x8E);
    idt_set_entry(17, exception_17, 0x08, 0x8E);
    idt_set_entry(18, exception_18, 0x08, 0x8E);
    idt_set_entry(19, exception_19, 0x08, 0x8E);
    idt_set_entry(20, exception_20, 0x08, 0x8E);
    idt_set_entry(21, exception_21, 0x08, 0x8E);
    idt_set_entry(22, exception_22, 0x08, 0x8E);
    idt_set_entry(23, exception_23, 0x08, 0x8E);
    idt_set_entry(24, exception_24, 0x08, 0x8E);
    idt_set_entry(25, exception_25, 0x08, 0x8E);
    idt_set_entry(26, exception_26, 0x08, 0x8E);
    idt_set_entry(27, exception_27, 0x08, 0x8E);
    idt_set_entry(28, exception_28, 0x08, 0x8E);
    idt_set_entry(29, exception_29, 0x08, 0x8E);
    idt_set_entry(30, exception_30, 0x08, 0x8E);
    idt_set_entry(31, exception_31, 0x08, 0x8E);
    idt_set_entry(32, irq_0, 0x08, 0x8E);
    idt_set_entry(33, irq_1, 0x08, 0x8E);
    idt_set_entry(34, irq_2, 0x08, 0x8E);
    idt_set_entry(35, irq_3, 0x08, 0x8E);
    idt_set_entry(36, irq_4, 0x08, 0x8E);
    idt_set_entry(37, irq_5, 0x08, 0x8E);
    idt_set_entry(38, irq_6, 0x08, 0x8E);
    idt_set_entry(39, irq_7, 0x08, 0x8E);
    idt_set_entry(40, irq_8, 0x08, 0x8E);
    idt_set_entry(41, irq_9, 0x08, 0x8E);
    idt_set_entry(42, irq_10, 0x08, 0x8E);
    idt_set_entry(43, irq_11, 0x08, 0x8E);
    idt_set_entry(44, irq_12, 0x08, 0x8E);
    idt_set_entry(45, irq_13, 0x08, 0x8E);
    idt_set_entry(46, irq_14, 0x08, 0x8E);
    idt_set_entry(47, irq_15, 0x08, 0x8E);
    idt_set_entry(128, exception_128, 0x08, 0x8E);

    load_idt((uint32_t)&g_idt_ptr);
    asm volatile("sti");

    logger_log("IDT Initialized\n");
}

#endif

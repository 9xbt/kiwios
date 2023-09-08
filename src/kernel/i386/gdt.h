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

#ifndef GDT_H
#define GDT_H

#include <inttypes.h>
#include "../utils/logger.h"

#define NO_GDT_DESCRIPTORS 8

typedef struct {
    uint16_t segment_limit;         // Segment limit first 0-15 bits
    uint16_t base_low;              // Base first 0-15 bits
    uint8_t base_middle;            // Base 16-23 bits
    uint8_t access;                 // Access byte
    uint8_t granularity;            // High 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
    uint8_t base_high;              // Base 24-31 bits
} __attribute__((packed)) GDT;

typedef struct {
    uint16_t limit;                 // Limit size of all GDT segments
    uint32_t base_address;          // Base address of the first GDT segment
} __attribute__((packed)) GDT_PTR;

// Load the GDT
extern void load_gdt(uint32_t gdt_ptr);

GDT g_gdt[NO_GDT_DESCRIPTORS];
GDT_PTR g_gdt_ptr;

// Fill GDT entries
void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    GDT *this = &g_gdt[index];

    this->segment_limit = limit & 0xFFFF;
    this->base_low = base & 0xFFFF;
    this->base_middle = (base >> 16) & 0xFF;
    this->access = access;

    this->granularity = (limit >> 16) & 0x0F;
    this->granularity = this->granularity | (gran & 0xF0);

    this->base_high = (base >> 24 & 0xFF);
}

// Initialize GDT
void gdt_init() {
    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base_address = g_gdt;

    gdt_set_entry(0, 0, 0, 0, 0);                  // Null segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // Code segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // Data segment
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   // User code segment
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   // User data segment

    load_gdt(&g_gdt_ptr);

    logger_log("GDT Initialized\n");
}

#endif

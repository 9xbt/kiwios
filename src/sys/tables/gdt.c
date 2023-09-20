/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include "gdt.h"

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

    term_print("[ OK ] ", 0x0A);
    term_print("GDT Initialized\n", 0x0F);
}

/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#pragma once

#include <inttypes.h>
#include <sys/drivers/terminal/terminal.h>

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
void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// Initialize GDT
void gdt_init();

#include "gdt.c"

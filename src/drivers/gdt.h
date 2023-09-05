/**
 * Global Descriptor Table(GDT) setup
 */\

 #ifndef GDT_H
 #define GDT_H

#include <inttypes.h>

#define NO_GDT_DESCRIPTORS     8

typedef struct {
    uint16_t segment_limit;  // segment limit first 0-15 bits
    uint16_t base_low;       // base first 0-15 bits
    uint8_t base_middle;     // base 16-23 bits
    uint8_t access;          // access byte
    uint8_t granularity;     // high 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
    uint8_t base_high;       // base 24-31 bits
} __attribute__((packed)) GDT;

typedef struct {
    uint16_t limit;       // limit size of all GDT segments
    uint32_t base_address;  // base address of the first GDT segment
} __attribute__((packed)) GDT_PTR;

GDT g_gdt[NO_GDT_DESCRIPTORS];
GDT_PTR g_gdt_ptr;

/**
 * fill entries of GDT 
 */
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

// initialize GDT
void gdt_init() {
    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base_address = (uint32_t)g_gdt;

    // NULL segment
    gdt_set_entry(0, 0, 0, 0, 0);
    // code segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // data segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // user code segment
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // user data segment
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt((uint32_t)&g_gdt_ptr);
}

#endif

/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include "isr.h"

// Register given handler to interrupt handlers at given number
void isr_register_interrupt_handler(int num, ISR handler) {
    if (num < NO_INTERRUPT_HANDLERS)
        g_interrupt_handlers[num] = handler;

    term_print("[ OK ] ", 0x0A);
    term_print("IRQ ", 0x0F);
    char buf[4];
    itoa(buf, 10, num);
    term_print(buf, 0x0F);
    term_print(" Registered\n", 0x0F);
}

// Turn off current interrupt
void isr_end_interrupt(int num) {
    pic_eoi(num);
}

// Invoke ISR routine and send EOI to PIC, being called in irq.asm
void isr_irq_handler(REGISTERS *reg) {
    if (g_interrupt_handlers[reg->int_no] != 0) {
        ISR handler = g_interrupt_handlers[reg->int_no];
        handler(reg);
    }
    pic_eoi(reg->int_no);
}

// Invoke exception routine, being called in exception.asm
void isr_exception_handler(REGISTERS reg) {
    if (reg.int_no < 32) {
        panic(exception_messages[reg.int_no]);
        for (;;);
    }
    
    if (g_interrupt_handlers[reg.int_no] != 0) {
        ISR handler = g_interrupt_handlers[reg.int_no];
        handler(&reg);
    }
}

void panic(const char* exception) {
    vga_init(0x11);
    
    term_setCursorPos(1, 1);
    term_print("     __\n   _ / /\n  (_) |\n   _| |\n  (_) |\n     \\_\\", 0x1F);    

    term_setCursorPos(12, 3);
    term_print("A problem has been detected and kiwios has had to shut down.", 0x1F);

    term_setCursorPos(12, 5);
    term_print("*** STOP: ", 0x1F);
    term_print(exception, 0x1F);
    term_print(" ***", 0x1F);

    for (;;);
}

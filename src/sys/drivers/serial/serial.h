/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef SERIAL_H
#define SERIAL_H

#define COM1 0x3F8          // COM1

#include <sys/hw/io.h>
#include <sys/drivers/terminal/terminal.h>
 
static void serial_init() {
    outb(COM1 + 1, 0x00);   // Disable all interrupts
    outb(COM1 + 3, 0x80);   // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03);   // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 1, 0x00);   //                  (hi byte)
    outb(COM1 + 3, 0x03);   // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);   // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);   // IRQs enabled, RTS/DSR set
    outb(COM1 + 4, 0x1E);   // Set in loopback mode, test the serial chip
    outb(COM1 + 0, 0xAE);   // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(COM1 + 0) != 0xAE) {
        term_print("[ OK ] ", 0x0E);
        term_print("Failed to initialize serial driver!\n", 0x0F);
    }
 
   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(COM1 + 4, 0x0F);
   term_print("[ OK ] ", 0x0A);
   term_print("Serial output enabled on COM1\n", 0x0F);
}

static int serial_received() {
   return inb(COM1 + 5) & 1;
}

static int serial_isTransmitEmpty() {
   return inb(COM1 + 5) & 0x20;
}
 
static char serial_read() {
   while (serial_received() == 0);
   return inb(COM1);
}
 
static void serial_send(const char a) {
   while (serial_isTransmitEmpty() == 0);
   outb(COM1, a);
}

static void serial_sendstring(const char *str) {
    int i = 0;
    while (str[i] != 0) {
        serial_send(str[i]);
        i++;
    }
}

#endif

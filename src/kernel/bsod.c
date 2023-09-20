/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include "bsod.h"

void showCrashScreen(const char *exception) {
    vga_init(0x11);
    
    term_setCursorPos(1, 1);
    term_print("     __\n   _ / /\n  (_) |\n   _| |\n  (_) |\n     \\_\\", 0x1F);    

    term_setCursorPos(12, 3);
    term_print("A problem has been detected and kiwios has had to shut down.", 0x1F);

    term_setCursorPos(12, 5);
    term_print("*** STOP: ", 0x1F);
    term_print(exception, 0x1F);
    term_print(" ***", 0x1F);
}
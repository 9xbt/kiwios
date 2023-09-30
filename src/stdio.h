/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#pragma once

#include <sys/drivers/terminal/terminal.h>
#include <string.h>

static void printf(const char *format, ...) {
    char **arg = (char **)&format;
    int c;
    char buf[32];

    arg++;

    memset(buf, 0, sizeof(buf));
    while ((c = *format++) != 0) {
        if (c != '%')
            term_printchar(c, 0x0F);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buf, c, *((int *)arg++));
                    p = buf;
                    goto string;
                    break;

                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";

                string:
                    for (p2 = p; *p2; p2++)
                        ;
                    for (; p2 < p + pad; p2++)
                        term_printchar(pad0 ? '0' : ' ', 0x0F);
                    while (*p)
                        term_printchar(*p++, 0x0F);
                    break;

                case '\n':
                    TERMINAL_X = 0;
                    TERMINAL_Y++;

                    if (TERMINAL_Y >= VGA_HEIGHT) {
                        term_scroll();
                    }
                    break;

                case '\r':
                    break;

                default:
                    term_printchar(*((int *)arg++), 0x0F);
                    break;
            }
        }
    }
}

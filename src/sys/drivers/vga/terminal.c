/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include "terminal.h"

void term_clear(void)
{
    vga_init(0x0F);
    TERMINAL_X = 0;
    TERMINAL_Y = 0;
}

void term_print(const char* str, const char col)
{
    int i = 0;
    bool printing = true;

    do
    {
        switch (*(str + i))
        {
            case '\0':
                printing = false;
                break;

            case '\n':
                TERMINAL_X = 0;
                TERMINAL_Y++;
                break;

            default:
                // Print the awaiting char
                *(char*)(VGA_BUFFER + (( (TERMINAL_Y * VGA_WIDTH) + TERMINAL_X) * 2)) = *(str + i);
                *(char*)(VGA_BUFFER + (( (TERMINAL_Y * VGA_WIDTH) + TERMINAL_X) * 2) + 1) = col;

                // Handle the cursor position
                TERMINAL_X++;

                if (TERMINAL_X >= VGA_WIDTH)
                {
                    TERMINAL_X = 0;
                    TERMINAL_Y++;
                }
                break;
        }

        if (TERMINAL_Y >= VGA_HEIGHT)
        {
            term_scroll();
        }

        i++;
    }
    while (printing);

    vga_movecursor(TERMINAL_X, TERMINAL_Y);
}

void term_println(const char* str, const char col)
{
    term_print(str, col);
    term_print("\n", 0x0F);
}

void term_printchar(const char chr, const char col)
{
    if (chr <= 0)
        return;

    // Print the awaiting char
    *(char*)(VGA_BUFFER + (((TERMINAL_Y * VGA_WIDTH) + TERMINAL_X) * 2)) = chr;
    *(char*)(VGA_BUFFER + (((TERMINAL_Y * VGA_WIDTH) + TERMINAL_X) * 2) + 1) = col;

    // Handle the cursor position
    TERMINAL_X++;

    if (TERMINAL_X >= VGA_WIDTH)
    {
        TERMINAL_X = 0;
        TERMINAL_Y++;
    }

    if (TERMINAL_Y >= VGA_HEIGHT)
    {
        term_scroll();
    }

    vga_movecursor(TERMINAL_X, TERMINAL_Y);
}

void term_scroll(void)
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++)
    {
        *(char*)(VGA_BUFFER + i) = *(char*)(VGA_BUFFER + i + (VGA_WIDTH * 2));
    }
    TERMINAL_X = 0;
    TERMINAL_Y = VGA_HEIGHT - 1;
}

void term_setCursorPos(char x, char y)
{
    vga_movecursor(x, y);
    TERMINAL_X = x;
    TERMINAL_Y = y;
}
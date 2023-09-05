#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>
#include "hal.h"

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 25

char* TERMINAL_BUFFER = (char*)0xB8000;

int TERMINAL_X = 0;
int TERMINAL_Y = 0;

void term_clear(void)
{
    for (int i = 0; i < TERMINAL_WIDTH * TERMINAL_HEIGHT * 2; i += 2)
    {
        *(TERMINAL_BUFFER + i) = 0x00;
        *(TERMINAL_BUFFER + i + 1) = 0x0F;
    }

    TERMINAL_X = 0;
    TERMINAL_Y = 0;
}

void term_print(char* str, char col)
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
                *(TERMINAL_BUFFER + (( (TERMINAL_Y * TERMINAL_WIDTH) + TERMINAL_X) * 2)) = *(str + i);
                *(TERMINAL_BUFFER + (( (TERMINAL_Y * TERMINAL_WIDTH) + TERMINAL_X) * 2) + 1) = col;

                // Handle the cursor position
                TERMINAL_X++;

                if (TERMINAL_X >= TERMINAL_WIDTH)
                {
                    TERMINAL_X = 0;
                    TERMINAL_Y++;
                }
                break;
        }

        if (TERMINAL_Y >= TERMINAL_HEIGHT)
        {
            term_scroll();
        }

        i++;
    }
    while (printing);

    term_setCursorPos(TERMINAL_X, TERMINAL_Y + 1);
}

void term_println(char* str, char col)
{
    term_print(str, col);
    term_print("\n", 0x0F);
}

void term_scroll()
{
    for (int i = 0; i < TERMINAL_WIDTH * TERMINAL_HEIGHT * 2; i++)
    {
        *(TERMINAL_BUFFER + i) = *(TERMINAL_BUFFER + i + (TERMINAL_WIDTH * 2));
    }
    TERMINAL_X = 0;
    TERMINAL_Y = TERMINAL_HEIGHT - 1;
}

void term_enableCursor()
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 1);
}

void term_setCursorPos(int x, int y)
{
	unsigned short int pos = y * TERMINAL_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

#endif
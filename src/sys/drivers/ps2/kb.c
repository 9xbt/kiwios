/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include "kb.h"

// Keyboard buffer
char kbd_buffer[256];
short int kbd_buffer_pos;

char alternate_chars(char ch) {
    switch(ch) {
        case '`': return '~';
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case ';': return ':';
        case '\'': return '\"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        default: return ch;
    }
}

void keyboard_handler() {
    int scancode;

    kbCh = 0;
    scancode = get_scancode();
    kbScanCode = scancode;
    if (scancode & 0x80) {
        // Key release
    } else {
        // Key down
        switch(scancode) {
            case SCAN_CODE_KEY_CAPS_LOCK:
                if (capsLock == false)
                    capsLock = true;
                else
                    capsLock = false;
                break;

            case SCAN_CODE_KEY_ENTER:
                kbCh = '\n';
                break;

            case SCAN_CODE_KEY_TAB:
                kbCh = '\t';
                break;

            case SCAN_CODE_KEY_LEFT_SHIFT:
                shiftPressed = true;
                break;

            default:
                kbCh = scancodes[scancode];
                if (capsLock) {                      // If caps in on, covert to upper
                    if (shiftPressed) {              // if shift is pressed before
                        kbCh = alternate_chars(kbCh);   // Replace alternate chars
                    } else
                        kbCh = upper(kbCh);
                } else {
                    if (shiftPressed) {
                        if (isalpha(kbCh))
                            kbCh = upper(kbCh);
                        else 
                        kbCh = alternate_chars(kbCh);   // Replace alternate chars
                    } else
                        kbCh = scancodes[scancode];
                    shiftPressed = false;
                }
                break;
        }
    }
}

void kbd_init() {
    isr_register_interrupt_handler(IRQ_BASE + 1, keyboard_handler);

    term_print("[ OK ] ", 0x0A);
    term_print("Keyboard Initialized\n", 0x0F);
}

// Blocking character read
char kbd_getchar() {
    char c;

    int s = get_scancode();
    while(s <= 0) {
        s = get_scancode();
    }

    c = kbCh;
    kbCh = 0;
    kbScanCode = 0;
    return c;
}

char* kbd_getstring() {
    //memset(kbd_buffer, 0x0, 256);

    for (int i = 0; i < 256; i++)
    {
        kbd_buffer[i] = 0x00;
    }

    bool reading = true;
    char startX = TERMINAL_X, startY = TERMINAL_Y;
    short int posInBuffer = 0;

    while (reading) {
        char key = kbd_getchar();

        switch (key) {
            case 0x0:
                break;

            case 0x8:
                if (!(TERMINAL_X == startX && TERMINAL_Y == startY)) {
                    if (TERMINAL_X == 0) {
                        TERMINAL_X = VGA_WIDTH - 1;
                        TERMINAL_Y--;
                        term_printchar(' ', 0x0F);
                        TERMINAL_X = VGA_WIDTH - 1;
                        TERMINAL_Y--;
                        vga_movecursor(TERMINAL_X, TERMINAL_Y);
                    }
                    else {
                        TERMINAL_X--;
                        term_printchar(' ', 0x0F);
                        TERMINAL_X--;
                        vga_movecursor(TERMINAL_X, TERMINAL_Y);
                    }

                    kbd_buffer[posInBuffer] = 0x0;
                    posInBuffer--;
                }
                break;
                
            case 0xA:
                if (posInBuffer < 256) {
                    term_print("\n", 0x0F);
                    kbd_buffer[posInBuffer] = 0x0;
                    reading = false;
                }
                break;
            
            default:
                if (posInBuffer < 256) {
                    term_printchar(key, 0x0F);

                    kbd_buffer[posInBuffer] = key;
                    posInBuffer++;
                }
                break;
        }
    }

    return kbd_buffer;
}

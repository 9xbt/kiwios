/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT                   0x60
#define KEYBOARD_STATUS_PORT                 0x64
#define KEYBOARD_COMMAND_PORT                0x64
#define SCAN_CODE_KEY_ESC                    0x01
#define SCAN_CODE_KEY_1                      0x02
#define SCAN_CODE_KEY_2                      0x03
#define SCAN_CODE_KEY_3                      0x04
#define SCAN_CODE_KEY_4                      0x05
#define SCAN_CODE_KEY_5                      0x06
#define SCAN_CODE_KEY_6                      0x07
#define SCAN_CODE_KEY_7                      0x08
#define SCAN_CODE_KEY_8                      0x09
#define SCAN_CODE_KEY_9                      0x0A
#define SCAN_CODE_KEY_0                      0x0B
#define SCAN_CODE_KEY_MINUS                  0x0C
#define SCAN_CODE_KEY_EQUAL                  0x0D
#define SCAN_CODE_KEY_BACKSPACE              0x0E
#define SCAN_CODE_KEY_TAB                    0x0F
#define SCAN_CODE_KEY_Q                      0x10
#define SCAN_CODE_KEY_W                      0x11
#define SCAN_CODE_KEY_E                      0x12
#define SCAN_CODE_KEY_R                      0x13
#define SCAN_CODE_KEY_T                      0x14
#define SCAN_CODE_KEY_Y                      0x15
#define SCAN_CODE_KEY_U                      0x16
#define SCAN_CODE_KEY_I                      0x17
#define SCAN_CODE_KEY_O                      0x18
#define SCAN_CODE_KEY_P                      0x19
#define SCAN_CODE_KEY_SQUARE_OPEN_BRACKET    0x1A
#define SCAN_CODE_KEY_SQUARE_CLOSE_BRACKET   0x1B
#define SCAN_CODE_KEY_ENTER                  0x1C
#define SCAN_CODE_KEY_LEFT_CTRL              0x1D
#define SCAN_CODE_KEY_A                      0x1E
#define SCAN_CODE_KEY_S                      0x1F
#define SCAN_CODE_KEY_D                      0x20
#define SCAN_CODE_KEY_F                      0x21
#define SCAN_CODE_KEY_G                      0x22
#define SCAN_CODE_KEY_H                      0x23
#define SCAN_CODE_KEY_J                      0x24
#define SCAN_CODE_KEY_K                      0x25
#define SCAN_CODE_KEY_L                      0x26
#define SCAN_CODE_KEY_SEMICOLON              0x27
#define SCAN_CODE_KEY_SINGLE_QUOTE           0x28
#define SCAN_CODE_KEY_ACUTE                  0x29
#define SCAN_CODE_KEY_LEFT_SHIFT             0x2A
#define SCAN_CODE_KEY_BACKSLASH              0x2B
#define SCAN_CODE_KEY_Z                      0x2C
#define SCAN_CODE_KEY_X                      0x2D
#define SCAN_CODE_KEY_C                      0x2E
#define SCAN_CODE_KEY_V                      0x2F
#define SCAN_CODE_KEY_B                      0x30
#define SCAN_CODE_KEY_N                      0x31
#define SCAN_CODE_KEY_M                      0x32
#define SCAN_CODE_KEY_COMMA                  0x33
#define SCAN_CODE_KEY_DOT                    0x34
#define SCAN_CODE_KEY_FORESLHASH             0x35
#define SCAN_CODE_KEY_RIGHT_SHIFT            0x36
#define SCAN_CODE_KEY_ASTERISK               0x37
#define SCAN_CODE_KEY_ALT                    0x38
#define SCAN_CODE_KEY_SPACE                  0x39
#define SCAN_CODE_KEY_CAPS_LOCK              0x3A
#define SCAN_CODE_KEY_F1                     0x3B
#define SCAN_CODE_KEY_F2                     0x3C
#define SCAN_CODE_KEY_F3                     0x3D
#define SCAN_CODE_KEY_F4                     0x3E
#define SCAN_CODE_KEY_F5                     0x3F
#define SCAN_CODE_KEY_F6                     0x40
#define SCAN_CODE_KEY_F7                     0x41
#define SCAN_CODE_KEY_F8                     0x42
#define SCAN_CODE_KEY_F9                     0x43
#define SCAN_CODE_KEY_F10                    0x44
#define SCAN_CODE_KEY_NUM_LOCK               0x45
#define SCAN_CODE_KEY_SCROLL_LOCK            0x46
#define SCAN_CODE_KEY_HOME                   0x47
#define SCAN_CODE_KEY_UP                     0x48
#define SCAN_CODE_KEY_PAGE_UP                0x49
#define SCAN_CODE_KEY_KEYPAD_MINUS           0x4A
#define SCAN_CODE_KEY_LEFT                   0x4B
#define SCAN_CODE_KEY_KEYPAD_5               0x4C
#define SCAN_CODE_KEY_RIGHT                  0x4D
#define SCAN_CODE_KEY_KEYPAD_PLUS            0x4E
#define SCAN_CODE_KEY_END                    0x4F
#define SCAN_CODE_KEY_DOWN                   0x50
#define SCAN_CODE_KEY_PAGE_DOWN              0x51
#define SCAN_CODE_KEY_INSERT                 0x52
#define SCAN_CODE_KEY_DELETE                 0x53
#define SCAN_CODE_KEY_F11                    0x57
#define SCAN_CODE_KEY_F12                    0x58

#include <inttypes.h>
#include <stdbool.h>
#include "idt.h"
#include "port.h"
#include "isr.h"
#include "../utils/string.h"
#include "../terminal.h"
#include "../utils/logger.h"

static bool g_caps_lock = false;
static bool g_shift_pressed = false;
char g_ch = 0, g_scan_code = 0;

// Scancodes
char g_scan_code_chars[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Keyboard buffer
char kbd_buffer[256];

// Get scancode
static int get_scancode() {
    int i, scancode = 0;

    // Get scancode until status is on (key pressed)
    for (i = 1000; i > 0; i++) {
        if ((inb(KEYBOARD_STATUS_PORT) & 1) == 0) continue; // Check if scan code is ready
        scancode = inb(KEYBOARD_DATA_PORT); // Get the scan code
        break;
    }
    if (i > 0)
        return scancode;
    return 0;
}

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

void keyboard_handler(REGISTERS *r) {
    int scancode;

    g_ch = 0;
    scancode = get_scancode();
    g_scan_code = scancode;
    if (scancode & 0x80) {
        // Key release
    } else {
        // Key down
        switch(scancode) {
            case SCAN_CODE_KEY_CAPS_LOCK:
                if (g_caps_lock == false)
                    g_caps_lock = true;
                else
                    g_caps_lock = false;
                break;

            case SCAN_CODE_KEY_ENTER:
                g_ch = '\n';
                break;

            case SCAN_CODE_KEY_TAB:
                g_ch = '\t';
                break;

            case SCAN_CODE_KEY_LEFT_SHIFT:
                g_shift_pressed = true;
                break;

            default:
                g_ch = g_scan_code_chars[scancode];
                if (g_caps_lock) {                      // If caps in on, covert to upper
                    if (g_shift_pressed) {              // if shift is pressed before
                        g_ch = alternate_chars(g_ch);   // Replace alternate chars
                    } else
                        g_ch = upper(g_ch);
                } else {
                    if (g_shift_pressed) {
                        if (isalpha(g_ch))
                            g_ch = upper(g_ch);
                        else 
                        g_ch = alternate_chars(g_ch);   // Replace alternate chars
                    } else
                        g_ch = g_scan_code_chars[scancode];
                    g_shift_pressed = false;
                }
                break;
        }

        if (g_ch > 0) {
            switch (g_scan_code) {
                case 0x0E:
                    TERMINAL_X--;
                    term_printchar(' ', 0x0F);
                    TERMINAL_X--;                    
                    break;

                default:
                    term_printchar(g_ch, 0x0F);
                    break;
            }
        }
    }
}

void kbd_init() {
    isr_register_interrupt_handler(IRQ_BASE + 1, keyboard_handler);
    log("Keyboard Initialized");
}

// Blocking character read
char kbd_getchar() {
    char c;

    while(g_ch < 0);
    c = g_ch;
    g_ch = 0;
    g_scan_code = 0;
    return c;
}

// Get scancode
char kbd_get_scancode() {
    char code;

    while(g_scan_code <= 0);
    code = g_scan_code;
    g_ch = 0;
    g_scan_code = 0;
    return code;
}

#endif

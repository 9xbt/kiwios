#include "drivers/terminal.h"

int kernel_main() {
    term_clear();
    term_print("Hello, world!", 0x02);
}
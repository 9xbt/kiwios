#include "drivers/terminal.h"

int kernel_main()
{
    term_enableCursor();
    
    term_clear();
    term_print("kiwiOS [build 230905]", 0x0F);
    term_println("\n _    _          _  ___  ____\n| | _(_)_      _(_)/ _ \\/ ___|\n| |/ / \\ \\ /\\ / / | | | \\___ \\\n|   <| |\\ V  V /| | |_| |___) |\n|_|\\_\\_| \\_/\\_/ |_|\\___/|____/\n", 0x0D);
    term_println("Copyright (c) 2023 kiwiorg", 0x0F);
    term_println("All rights reserved\n", 0x0F);
}

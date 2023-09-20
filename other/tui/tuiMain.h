//
// Created by ekeleze on 9/19/23.
//

#ifndef KIWIOS_TUIMAIN_H
#define KIWIOS_TUIMAIN_H

int maxSel = 0;
int cSel = 0;

char full_line[] = "████████████████████████████████████████████████████████████████████████████████";
char empty_line[] = "█                                                                              █";

static void tuiMain(void);

static void selectionHandler(bool Up);

#include "../src/tui/tuiMain.c"

#endif //KIWIOS_TUIMAIN_H

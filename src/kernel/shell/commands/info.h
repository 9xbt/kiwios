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

#ifndef INFO_H
#define INFO_H

#include "../../common.h"
#include "../../terminal.h"
#include "../../i386/vga.h"

void cmd_info() {
    term_println(buildstr, 0x07);
    term_println(logostr, 0x0D);
    term_println(copyrightstr, 0x07);
    term_println(licensestr, 0x07); 
}

#endif

/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#pragma once

#include <inttypes.h>
#include <sys/tables/isr.h>
#include <sys/drivers/terminal/terminal.h>

typedef struct {
	uint8_t status;
	uint32_t size;
} alloc_t;

void mm_init(uint32_t kernel_end);
void mm_print_out();

char* pmalloc(size_t size); /* page aligned alloc */
char* malloc(size_t size);
void free(void *mem);

#include "memory.c"

/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef __DEVICE_H_
#define __DEVICE_H_

#include <sys/hw/io.h>
#include <sys/drivers/terminal/terminal.h>
#include <sys/memory/memory.h>
#include <inttypes.h>

struct __fs_t;

typedef enum __device_type {
	DEVICE_UNKNOWN = 0,
	DEVICE_CHAR = 1,
	DEVICE_BLOCK = 2,
} device_type;


typedef struct __device_t {
	char *name;
	uint32_t unique_id;
	device_type dev_type;
	struct __fs_t *fs;
	uint8_t (*read)(uint8_t* buffer, uint32_t offset , uint32_t len, void* dev);
	uint8_t (*write)(uint8_t *buffer, uint32_t offset, uint32_t len, void* dev);
	void *priv;
} device_t;

void device_print_out();
void device_init();
int device_add(device_t* dev);
int device_getnumber();
device_t *device_get(uint32_t id);
device_t *device_get_by_id(uint32_t id);

#include "device.c"

#endif
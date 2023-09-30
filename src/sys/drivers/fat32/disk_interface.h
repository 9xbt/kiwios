/*
 * fat32 - Tiny FAT32 file system implementation
 * Copyright (c) 2020 StrawberryHacker
 */

#pragma once

#include <sys/drivers/ide/ide.h>
#include "fat_types.h"

/// Add new physical disk here
typedef enum {
	DISK_HD1
} disk_t;

// Returns the status of the MSD (mass storage device)
u8 disk_get_status(disk_t disk);

// Initializes at disk intrface
u8 disk_initialize(disk_t disk);

// Read a number of sectors from the MSD
u8 disk_read(disk_t disk, u8* buffer, u32 lba, u32 count);

// Write a number of sectors to the MSD
u8 disk_write(disk_t disk, const u8* buffer, u32 lba, u32 count);

#include "disk_interface.c"

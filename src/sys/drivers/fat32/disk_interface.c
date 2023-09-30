/*
 * fat32 - Tiny FAT32 file system implementation
 * Copyright (c) 2020 StrawberryHacker
 */

#include "disk_interface.h"

u8 disk_get_status(disk_t disk) {
	switch (disk) {
		case DISK_HD1: {
			return 1;
		}
	}
	return 0;
}

u8 disk_initialize(disk_t disk) {
	switch (disk) {
		case DISK_HD1: {
			ata_init();
		}
	}
	return 0;
}

u8 disk_read(disk_t disk, u8* buffer, u32 lba, u32 count) {
	switch (disk) {
		case DISK_HD1: {
            return ide_read_sectors(0, count, lba, buffer);
		}
	}
	return 0;
}

u8 disk_write(disk_t disk, const u8* buffer, u32 lba, u32 count) {
	switch (disk) {
		case DISK_HD1: {
			return ide_write_sectors(0, count, lba, buffer);
		}
	}
	return 0;
}
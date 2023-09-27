/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include "ata.h"

#define ATA_PRIMARY_IO         0x1F0
#define ATA_SECONDARY_IO       0x170

#define ATA_PRIMARY_DCR_AS     0x3F6
#define ATA_SECONDARY_DCR_AS   0x376

#define ATA_PRIMARY_IRQ        0xE
#define ATA_SECONDARY_IRQ      0XF

uint8_t ata_pm = 0; /* Primary master exists? */
uint8_t ata_ps = 0; /* Primary Slave exists? */
uint8_t ata_sm = 0; /* Secondary master exists? */
uint8_t ata_ss = 0; /* Secondary slave exists? */

uint8_t *ide_buf = 0;

void ide_select_drive(uint8_t bus, uint8_t i)
{
	if(bus == ATA_PRIMARY)
		if(i == ATA_MASTER)
			outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xB0);
	else
		if(i == ATA_MASTER)
			outb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else outb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xB0);
}

void ide_primary_irq()
{
	pic_eoi(ATA_PRIMARY_IRQ);
}

void ide_secondary_irq()
{
	pic_eoi(ATA_SECONDARY_IRQ);
}

uint8_t ide_identify(uint8_t bus, uint8_t drive)
{
	uint16_t io = 0;
	ide_select_drive(bus, drive);
	if(bus == ATA_PRIMARY) io = ATA_PRIMARY_IO;
	else io = ATA_SECONDARY_IO;
	/* ATA specs say these values must be zero before sending IDENTIFY */
	outb(io + ATA_REG_SECCOUNT0, 0);
	outb(io + ATA_REG_LBA0, 0);
	outb(io + ATA_REG_LBA1, 0);
	outb(io + ATA_REG_LBA2, 0);
	/* Now, send IDENTIFY */
	outb(io + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
	/* Now, read status port */
	uint8_t status = inb(io + ATA_REG_STATUS);
	if(status)
	{
		/* Now, poll untill BSY is clear. */
		while(inb(io + ATA_REG_STATUS) & ATA_SR_BSY != 0);

    pm_stat_read:
        status = inb(io + ATA_REG_STATUS);
		if(status & ATA_SR_ERR)
		{
            term_print("[WARN] ", 0x0E);
            term_print(bus == ATA_PRIMARY ? "Primary" : "Secondary", 0x0F);
            term_print(drive == ATA_PRIMARY ? " Master" : " Slave", 0x0F);
            term_print(" disabled due to error", 0x0F);
			return 0;
		}
		while(!(status & ATA_SR_DRQ)) goto pm_stat_read;
        term_print("[ OK ] ", 0x0A);
		term_print("ATA ", 0x0F);
        term_print(bus == ATA_PRIMARY ? "Primary" : "Secondary", 0x0F);
        term_println(drive == ATA_PRIMARY ? " Master" : " Slave", 0x0F);
		/* Now, actually read the data */
		for(int i = 0; i<256; i++)
		{
			*(uint16_t *)(ide_buf + i*2) = inw(io + ATA_REG_DATA);
		}
	}

	return 1;
}

void ide_400ns_delay(uint16_t io)
{
	for(int i = 0;i < 4; i++)
		inb(io + ATA_REG_ALTSTATUS);
}

void ide_poll(uint16_t io)
{
	for(int i=0; i< 4; i++)
		inb(io + ATA_REG_ALTSTATUS);

retry:;
	uint8_t status = inb(io + ATA_REG_STATUS);
	if(status & ATA_SR_BSY) goto retry;
retry2:	status = inb(io + ATA_REG_STATUS);
	if(status & ATA_SR_ERR)
	{
		panic("Device failiure\n");
	}
	if(!(status & ATA_SR_DRQ)) goto retry2;
	return;
}

uint8_t ata_read_one(uint8_t *buf, uint32_t lba, device_t *dev)
{
	/* We only support 28bit LBA so far */
	uint8_t drive = ((ide_private_data *)(dev->priv))->drive;
	uint16_t io = 0;
	switch(drive)
	{
		case (ATA_PRIMARY << 1 | ATA_MASTER):
			io = ATA_PRIMARY_IO;
			drive = ATA_MASTER;
			break;
		case (ATA_PRIMARY << 1 | ATA_SLAVE):
			io = ATA_PRIMARY_IO;
			drive = ATA_SLAVE;
			break;
		case (ATA_SECONDARY << 1 | ATA_MASTER):
			io = ATA_SECONDARY_IO;
			drive = ATA_MASTER;
			break;
		case (ATA_SECONDARY << 1 | ATA_SLAVE):
			io = ATA_SECONDARY_IO;
			drive = ATA_SLAVE;
			break;
		default:
            term_print("[FAIL] ", 0x0C);
			term_print("Unknown drive!\n", 0x0F);
			return 0;
	}
	//kprintf("io=0x%x %s\n", io, drive==ATA_MASTER?"Master":"Slave");
	uint8_t cmd = (drive==ATA_MASTER?0xE0:0xF0);
	uint8_t slavebit = (drive == ATA_MASTER?0x00:0x01);
	/*kprintf("LBA = 0x%x\n", lba);
	kprintf("LBA>>24 & 0x0f = %d\n", (lba >> 24)&0x0f);
	kprintf("(uint8_t)lba = %d\n", (uint8_t)lba);
	kprintf("(uint8_t)(lba >> 8) = %d\n", (uint8_t)(lba >> 8));
	kprintf("(uint8_t)(lba >> 16) = %d\n", (uint8_t)(lba >> 16));*/
	//outb(io + ATA_REG_HDDEVSEL, cmd | ((lba >> 24)&0x0f));
	outb(io + ATA_REG_HDDEVSEL, (cmd | (uint8_t)((lba >> 24 & 0x0F))));
	//mprint("issued 0x%x to 0x%x\n", (cmd | (lba >> 24)&0x0f), io + ATA_REG_HDDEVSEL);
	//for(int k = 0; k < 10000; k++) ;
	outb(io + 1, 0x00);
	//mprint("issued 0x%x to 0x%x\n", 0x00, io + 1);
	//for(int k = 0; k < 10000; k++) ;
	outb(io + ATA_REG_SECCOUNT0, 1);
	//mprint("issued 0x%x to 0x%x\n", (uint8_t) numsects, io + ATA_REG_SECCOUNT0);
	//for(int k = 0; k < 10000; k++) ;
	outb(io + ATA_REG_LBA0, (uint8_t)((lba)));
	//mprint("issued 0x%x to 0x%x\n", (uint8_t)((lba)), io + ATA_REG_LBA0);
	//for(int k = 0; k < 10000; k++) ;
	outb(io + ATA_REG_LBA1, (uint8_t)((lba) >> 8));
	//mprint("issued 0x%x to 0x%x\n", (uint8_t)((lba) >> 8), io + ATA_REG_LBA1);
	//for(int k = 0; k < 10000; k++) ;
	outb(io + ATA_REG_LBA2, (uint8_t)((lba) >> 16));
	//mprint("issued 0x%x to 0x%x\n", (uint8_t)((lba) >> 16), io + ATA_REG_LBA2);
	//for(int k = 0; k < 10000; k++) ;
	outb(io + ATA_REG_COMMAND, ATA_CMD_READ_PIO);
	//mprint("issued 0x%x to 0x%x\n", ATA_CMD_READ_PIO, io + ATA_REG_COMMAND);

	ide_poll(io);

	for(int i = 0; i < 256; i++)
	{
		uint16_t data = inw(io + ATA_REG_DATA);
		*(uint16_t *)(buf + i * 2) = data;
	}
	ide_400ns_delay(io);
	return 1;
}

void ata_read(uint8_t *buf, uint32_t lba, uint32_t numsects, device_t *dev)
{
	for(int i = 0; i < numsects; i++)
	{
		ata_read_one(buf, lba + i, dev);
		buf += 512;
	}
}

void ata_probe()
{
	// First check the primary bus, and inside the master drive.
	
	if (ide_identify(ATA_PRIMARY, ATA_MASTER))
	{
		ata_pm = 1;
		device_t *dev = (device_t *)malloc(sizeof(device_t));
		ide_private_data *priv = (ide_private_data *)malloc(sizeof(ide_private_data));
		/* Now, process the IDENTIFY data */
		/* Model goes from W#27 to W#46 */
		char *str = (char *)malloc(40);
		for(int i = 0; i < 40; i += 2)
		{
			str[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			str[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}
		dev->name = str;
		dev->unique_id = 32;
		dev->dev_type = DEVICE_BLOCK;
		priv->drive = (ATA_PRIMARY << 1) | ATA_MASTER;
		dev->priv = priv;
		dev->read = ata_read;
		device_add(dev);
	}

	// wont work for some reason, but we dont need them for now so they'll stay commented out
	//ide_identify(ATA_PRIMARY, ATA_SLAVE);
	//ide_identify(ATA_SECONDARY, ATA_MASTER);
	//ide_identify(ATA_SECONDARY, ATA_SLAVE);
}

void ata_init()
{
	ide_buf = (uint16_t *)malloc(512);
	isr_register_interrupt_handler(IRQ_BASE + ATA_PRIMARY_IRQ, ide_primary_irq);
	isr_register_interrupt_handler(IRQ_BASE + ATA_SECONDARY_IRQ, ide_secondary_irq);
	ata_probe();
	term_print("[ OK ] ", 0x0A);
	term_print("ATA Initialized\n", 0x0F);
}

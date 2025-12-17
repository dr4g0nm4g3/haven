/*
 * sysinfo.c
 *
 *	functions to gather information about the system
 *
 *  Created on: Mar 1, 2009
 *      Author: Jeff DiClemente
 */

#include <system.h>
#include <kernel.h>
#include <multiboot.h>
#include <kdbg.h>

/* detect available RAM */
void detect_memory(void * mbh)
{
	multiboot_info_t * mbinfo = (multiboot_info_t *)mbh;

	kdbg_log("memory info:\n");
	kdbg_log("*********************\n");
	kdbg_log("mem lower: %l KB \n", mbinfo->mem_lower);
	kdbg_log("mem upper: %l KB \n", mbinfo->mem_upper);

	// if bit 6 of flags is set, a valid memory map exists
	if( CHECK_FLAG(mbinfo->flags, 6) )
	{
		memory_map_t * mmap = (memory_map_t *) mbinfo->mmap_addr;
		unsigned int count = 0;
		while(mmap < (memory_map_t *)mbinfo->mmap_addr + mbinfo->mmap_length)
		{
			if(mmap->type == 1)
			{
				kdbg_log("size: 0x%x\nbase address: 0x%x%x\nlength: 0x%x%x\nmemory type: 0x%x\n",
						mmap->size, mmap->base_addr_high, mmap->base_addr_low,
						mmap->length_high, mmap->length_low, mmap->type);
			}

			count++;
			mmap = (memory_map_t *) ((unsigned long)mmap + mmap->size + sizeof(mmap->size));
		}
		kdbg_log("Number of mmap structs: %d \n", count);
	}
}

/* detect IO devices */
void detect_devices(void * mbh)
{
	multiboot_info_t * mbinfo = (multiboot_info_t *)mbh;

	kdbg_log("detected drives\n");
	kdbg_log("******************\n");

	/* bit 7 of flags determines whether there is information in the drives_* structure */
	if( CHECK_FLAG(mbinfo->flags, 7) )
	{
		drive_map_t * drive_info = (drive_map_t *) mbinfo->drives_addr;

		if(mbinfo->drives_length == 0)
		{
			kdbg_log("no drive information available\n");
			return;
		}

		kdbg_log("drive_addr = 0x%x\ndrives_length = 0x%x\n", mbinfo->drives_addr, mbinfo->drives_length);

		unsigned long current_pointer = (unsigned long)drive_info;
		unsigned long maximum_address = (unsigned long) mbinfo->drives_addr + mbinfo->drives_length;

		while(current_pointer < maximum_address)
		{
			char drive_num = drive_info->drive_num;
			char drive_mode =  drive_info->drive_mode;
			unsigned short cylinders =  drive_info->drive_cylinders;
			char sectors =  drive_info->drive_sectors;
			char heads =  drive_info->drive_heads;
			kdbg_log("drive_info->size = %d\n", drive_info->size);
			kdbg_log("Drive number: %d\n", drive_num);
			kdbg_log("Drive mode: %s\n", (drive_mode == 0)? "CHS mode":"LBA mode");
			kdbg_log("Drive cylinders: %d\n", cylinders);
			kdbg_log("Drive sectors: %d\n", sectors);
			kdbg_log("Drive heads: %d\n", heads);

			//TODO: display drive ports

			drive_info = (drive_map_t *)((unsigned long)drive_info + drive_info->size);
			current_pointer = (unsigned long)drive_info;
		}
	}
	else
		kdbg_log("No information available\n");
}

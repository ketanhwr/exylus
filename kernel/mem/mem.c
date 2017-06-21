/*
 * mem.c
 *
 * This file is a part of Exylus.
 */

#include "mem.h"

#include "isr.h"
#include "string.h"
#include "tty.h"

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

uint32_t *frames;
uint32_t nframes;

extern uintptr_t end;
uintptr_t placement_address = (uintptr_t)&end;

uint32_t kmalloc(uint32_t sz)
{
	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}

uint32_t kmalloc_a(uint32_t sz)
{
	if (placement_address & 0xFFFFF000) {
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}
	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
	if (placement_address & 0xFFFFF000) {
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}
	if (phys) {
		*phys = placement_address;
	}
	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}

static void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

static uint32_t first_frame()
{
	uint32_t i, j;
	for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
		if (frames[i] != 0xFFFFFFFF) {
			for (j = 0; j < 32; j++) {
				uint32_t toTest = 0x1 << j;
				if (!(frames[i] & toTest)) {
					return i*4*8+j;
				}
			}
		}
	}
	return 0;
}

void alloc_frame(page_t *page, int32_t is_kernel, int32_t is_writeable)
{
	if (page->frame != 0) {
		return;
	} else {
		uint32_t idx = first_frame();
		if (idx == (uint32_t)-1) {
			asm volatile ("cli");
			for(;;);
		}
		set_frame(idx*0x1000);
		page->present = 1;
		page->rw = (is_writeable)?1:0;
		page->user = (is_kernel)?0:1;
		page->frame = idx;
	}
}

void free_frame(page_t *page)
{
	uint32_t frame;
	if (!(frame=page->frame)) {
		return;
	} else {
		clear_frame(frame);
		page->frame = 0x0;
	}
}

void init_paging()
{
	uint32_t mem_end_page = 0x1000000;

	nframes = mem_end_page / 0x1000;
	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	uint32_t i = 0;
	while (i < placement_address) {
		alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}
	isr_install_handler(14, page_fault);

	switch_page_directory(kernel_directory);

	UNUSED(test_frame);
}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uintptr_t address, int32_t make, page_directory_t *dir)
{
	address /= 0x1000;
	uint32_t table_idx = address / 1024;
	if (dir->tables[table_idx]) {
		return &dir->tables[table_idx]->pages[address%1024];
	} else if(make) {
		uint32_t tmp;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
		memset(dir->tables[table_idx], 0, 0x1000);
		dir->tablesPhysical[table_idx] = tmp | 0x7;
		return &dir->tables[table_idx]->pages[address%1024];
	} else {
		return 0;
	}
}

void page_fault(registers_t *regs)
{
	uint32_t faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	int32_t present = !(regs->err_code & 0x1);
	int32_t rw = regs->err_code & 0x2;
	int32_t us = regs->err_code & 0x4;
	int32_t reserved = regs->err_code & 0x8;

	terminal_writestring("Page fault! ( ");
	if (present) {terminal_writestring("present ");}
	if (rw) {terminal_writestring("read-only ");}
	if (us) {terminal_writestring("user-mode ");}
	if (reserved) {terminal_writestring("reserved ");}
	terminal_writestring(") at 0x");
	terminal_writehex(faulting_address);
	terminal_writestring("\n");

	asm volatile ("cli");
	for(;;);
}

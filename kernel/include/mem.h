/*
 * mem.h
 *
 * This file is a part of Exylus.
 */

#include "system.h"

#include <stdint.h>

typedef struct page
{
	uint32_t present : 1;
	uint32_t rw : 1;
	uint32_t user : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t unused : 7;
	uint32_t frame : 20;
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
	page_table_t *tables[1024];
	
	uint32_t tablesPhysical[1024];

	uint32_t physicalAddr;
} page_directory_t;

page_directory_t * kernel_directory;
page_directory_t * current_directory;

void init_paging();

void switch_page_directory(page_directory_t *new);

page_t *get_page(uint32_t address, int32_t make, page_directory_t *dir);

void page_fault(registers_t *regs);

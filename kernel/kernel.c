/*
 * kernel.c
 *
 * This file is a part of Exylus.
 */

#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "mem.h"
#include "timer.h"
#include "tty.h"

void kernel_main()
{
	init_gdt();
	init_idt();
	init_irq();
	init_timer();
	init_keyboard();
	init_paging();

	terminal_initialize();

	terminal_writestring("  ______            _           \n");
	terminal_writestring(" |  ____|          | |          \n");
	terminal_writestring(" | |__  __  ___   _| |_   _ ___ \n");
	terminal_writestring(" |  __| \\ \\/ / | | | | | | / __|\n");
	terminal_writestring(" | |____ >  <| |_| | | |_| \\__ \\\n");
	terminal_writestring(" |______/_/\\_\\\\__, |_|\\__,_|___/\n");
	terminal_writestring("               __/ |            \n");
	terminal_writestring("              |___/             \n");

	terminal_writestring("\n");
	terminal_writestring("Firing an exception!\n");
	asm volatile ("int $0x0");

	terminal_newline();

	terminal_writestring("Delay for 2 seconds!\n");
	timer_wait(2);
	terminal_writestring("Delay complete!\n\n");

	terminal_writestring("Creating page fault!\n");
	uint32_t *ptr = (uint32_t*)0xA0000000;
	volatile uint32_t do_page_fault = *ptr;
	UNUSED(do_page_fault);

	for(;;);
}

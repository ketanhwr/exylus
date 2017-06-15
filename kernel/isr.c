/*
 * isr.c
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

#include "isr.h"

#include "tty.h"

void isr_handler(registers_t *regs)
{
	if (regs->int_no < 32) {
		terminal_writestring("Interrupt: ");
		terminal_writeint(regs->int_no);
		terminal_writestring("\n");
	}
}

/*
 * isr.h
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

#include <stdint.h>

typedef struct registers
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
} registers_t;

void isr_handler(registers_t *regs);

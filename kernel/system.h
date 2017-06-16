/*
 * system.h
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

#pragma once

#include <stdint.h>

#define UNUSED(x) (void)(x)
#define CLOCK_FREQUENCY 100

typedef struct registers
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void outb(uint16_t port, uint8_t val);

uint8_t inb(uint16_t port);

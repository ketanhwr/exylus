/*
 * kernel.c
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

#include "vga.h"

void kernel_main ()
{
	terminal_initialize();
	terminal_writestring("Exylus..!\n");
}

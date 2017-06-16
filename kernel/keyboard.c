/*
 * keyboard.c
 *
 * This file is a part of Exylus.
 */

#include "keyboard.h"

#include "irq.h"
#include "tty.h"

unsigned char keycode[128] =
{
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
	'9', '0', '-', '=', '\b',
	'\t',
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	'\'', '`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',
	'm', ',', '.', '/', 0,
	'*',
	0,
	' ',
	0,
	0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0,
	0,
	0,
	'-',
	0,
	0,
	0,
	'+',
	0,
	0,
	0,
	0,
	0,
	0, 0, 0,
	0,
	0,
	0,
};

void kb_handler(registers_t *reg)
{
	UNUSED(reg);

	unsigned char scancode = inb(0x60);

	if (!(scancode & 0x80)) {
		terminal_putchar(keycode[scancode]);
	}
}

void init_keyboard()
{
	irq_install_handler(1, kb_handler);
}

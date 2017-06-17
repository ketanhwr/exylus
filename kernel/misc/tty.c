/*
 * tty.c
 *
 * This file is a part of Exylus.
 */

#include "tty.h"

#include "string.h"
#include "system.h"
#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t *) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}

	update_cursor();
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void update_cursor()
{
	size_t x = terminal_column, y = terminal_row;

	const size_t index = y * VGA_WIDTH + x;

	outb(0x3D4, 14);
	outb(0x3D5, index>> 8);
	outb(0x3D4, 15);
	outb(0x3D5, index);
}

void terminal_scroll()
{
	for (size_t y = 0; y < VGA_HEIGHT - 1; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x) {
			const size_t index = y * VGA_WIDTH + x;
			const size_t index2 = (y + 1) * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[index2];
		}
	}

	for (size_t x = 0; x < VGA_WIDTH; ++x) {
		const size_t index = VGA_WIDTH * (VGA_WIDTH - 1) + x;
		terminal_buffer[index] = vga_entry(' ', terminal_column);
	}

	--terminal_row;
	update_cursor();
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n') {
		++terminal_row;
		terminal_column = 0;

		if (terminal_row == VGA_HEIGHT - 1) {
			terminal_scroll();
		}
	} else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;

			if (++terminal_row == VGA_HEIGHT - 1) {
				terminal_scroll();
			}
		}
	}

	update_cursor();
}

void terminal_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		terminal_putchar(data[i]);
	}
}

void terminal_writestring(const char *data)
{
	terminal_write(data, strlen(data));
}

void terminal_writedigit(uint8_t digit)
{
	terminal_putchar('0' + digit);
}

void terminal_writeint(int32_t value)
{
	if (value < 0) {
		terminal_putchar('-');
		value = value * (-1);
	}

	if (value == 0) {
		terminal_writedigit(0);
		return;
	}

	int32_t rev = 0;
	while (value > 0) {
		rev = rev * 10 + value%10;
		value /= 10;
	}

	while (rev > 0) {
		terminal_writedigit(rev%10);
		rev /= 10;
	}
}

void terminal_newline()
{
	terminal_putchar('\n');
}

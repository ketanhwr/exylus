/*
 * tty.h
 *
 * This file is a part of Exylus.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void);

void terminal_setcolor(uint8_t color);

void update_cursor();

void terminal_scroll();

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

void terminal_putchar(char c);

void terminal_write(const char *data, size_t size);

void terminal_writestring(const char *data);

void terminal_writedigit(uint8_t digit);

void terminal_writeint(int32_t value);

void terminal_newline();

void terminal_writehex(uint32_t num);

/*
 * string.c
 *
 * This file is a part of Exylus.
 */

#include "string.h"

void *memset(void *dst, int c, size_t count)
{
	char *p = (char *)dst;

	for (; count != 0; --count)
		*p++ = c;

    return dst;
}

size_t strlen(const char *str)
{
	size_t len = 0;
	while (str[len]) {
		len++;
	}
	return len;
}

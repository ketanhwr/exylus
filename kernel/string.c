/*
 * string.c
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
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
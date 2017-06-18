/*
 * stddef.h
 *
 * This file is a part of Exylus.
 */

#ifndef STDDEF_H
#define STDDEF_H

/**
 * Definitions
 */

/* Definition: NULL */
#ifndef NULL
#define NULL    0
#endif

/* Definition: size_t */
#ifndef __SIZE_TYPE_
#define __SIZE_TYPE_ long unsigned int
typedef __SIZE_TYPE_ size_t;
#endif

#endif /* STDDEF_H */

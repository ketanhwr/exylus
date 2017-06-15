/*
 * idt.s
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

.global idt_flush
.type idt_flush, @function
idt_flush:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

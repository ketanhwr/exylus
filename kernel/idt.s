/*
 * idt.s
 *
 * This file is a part of Exylus.
 */

.global idt_flush
.type idt_flush, @function
idt_flush:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

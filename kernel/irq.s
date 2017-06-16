/*
 * irq.s
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15

.type irq0, @function
irq0:
	cli
	pushl $0
	pushl $32
	jmp irq_common_stub

.type irq1, @function
irq1:
	cli
	pushl $0
	pushl $33
	jmp irq_common_stub

.type irq2, @function
irq2:
	cli
	pushl $0
	pushl $34
	jmp irq_common_stub

.type irq3, @function
irq3:
	cli
	pushl $0
	pushl $35
	jmp irq_common_stub

.type irq4, @function
irq4:
	cli
	pushl $0
	pushl $36
	jmp irq_common_stub

.type irq5, @function
irq5:
	cli
	pushl $0
	pushl $37
	jmp irq_common_stub

.type irq6, @function
irq6:
	cli
	pushl $0
	pushl $38
	jmp irq_common_stub

.type irq7, @function
irq7:
	cli
	pushl $0
	pushl $39
	jmp irq_common_stub

.type irq8, @function
irq8:
	cli
	pushl $0
	pushl $40
	jmp irq_common_stub

.type irq9, @function
irq9:
	cli
	pushl $0
	pushl $41
	jmp irq_common_stub

.type irq10, @function
irq10:
	cli
	pushl $0
	pushl $42
	jmp irq_common_stub

.type irq11, @function
irq11:
	cli
	pushl $0
	pushl $43
	jmp irq_common_stub

.type irq12, @function
irq12:
	cli
	pushl $0
	pushl $44
	jmp irq_common_stub

.type irq13, @function
irq13:
	cli
	pushl $0
	pushl $45
	jmp irq_common_stub

.type irq14, @function
irq14:
	cli
	pushl $0
	pushl $46
	jmp irq_common_stub

.type irq15, @function
irq15:
	cli
	pushl $0
	pushl $47
	jmp irq_common_stub

.type irq_common_stub, @function
irq_common_stub:
	pusha
	push %ds
	push %es
	push %fs
	push %gs
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movl %esp, %eax
	pushl %eax
	movl $irq_handler, %eax
	call *%eax
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	addl $8, %esp
	iret

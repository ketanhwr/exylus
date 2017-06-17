/*
 * start.s
 *
 * This file is a part of Exylus.
 */

.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp

	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start

.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	mov 4(%esp), %eax
	lgdt (%eax)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %ss

	jmp $0x08, $.flush
.flush:
	ret

.global idt_flush
.type idt_flush, @function
idt_flush:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

.macro ISR_NOERRCODE count
	.global isr\count
	.type isr\count, @function
	isr\count:
    	cli
    	pushl $0
    	pushl $\count
    	jmp isr_common_stub
.endm

.macro ISR_ERRCODE count
	.global isr\count
	.type isr\count, @function
	isr\count:
    	cli
    	pushl $\count
    	jmp isr_common_stub
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

.type isr_common_stub, @function
isr_common_stub:
	pusha
	push %ds
	push %es
	push %fs
	push %gs
	movw $0x10,%ax
	movw %ax,%ds
	movw %ax,%es
	movw %ax,%fs
	movw %ax,%gs
	movl %esp,%eax
	pushl %eax
	movl $isr_handler, %eax
	call *%eax
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	addl $8,%esp
	iret

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

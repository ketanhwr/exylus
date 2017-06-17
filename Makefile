AS=i686-elf-as
CC=i686-elf-gcc

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

KERNEL_OBJ_LIST:=\
kernel/gdt.o \
kernel/idt.o \
kernel/irq.o \
kernel/isr.o \
kernel/kernel.o \
kernel/keyboard.o \
kernel/string.o \
kernel/system.o \
kernel/timer.o \
kernel/tty.o \
kernel/vga.o

all: $(KERNEL_OBJ_LIST) kernel/start.s
	$(CC) -T linker/linker.ld -o exylus.bin -ffreestanding -O2 -nostdlib $^ -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

run:
	qemu-system-i386 -kernel exylus.bin

clean:
	find -type f \( -name "*.o" -o -name "*.bin" \) -delete
AS=i686-elf-as
CC=i686-elf-gcc

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

KERNEL_CC_LIST:=\
kernel/cpu/gdt.o \
kernel/cpu/idt.o \
kernel/cpu/irq.o \
kernel/cpu/isr.o \
kernel/devices/timer.o \
kernel/devices/keyboard.o \
kernel/misc/tty.o \
kernel/misc/vga.o \
kernel/sys/system.o \
kernel/kernel.o \
kernel/libc.o

KERNEL_AS_LIST:=\
kernel/core.o

KERNEL_INCLUDE_DIR=kernel/include

all: kernel

kernel: $(KERNEL_CC_LIST) $(KERNEL_AS_LIST)
	$(CC) -T linker/linker.ld -o exylus.bin -ffreestanding -O2 -nostdlib $^ -lgcc -I$(KERNEL_INCLUDE_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(KERNEL_INCLUDE_DIR)

%.o: %.s
	$(AS) $< -o $@

run:
	qemu-system-i386 -kernel exylus.bin

iso: kernel
	cp exylus.bin iso/boot/exylus.bin
	grub-mkrescue -o exylus.iso iso/

run-iso: iso
	qemu-system-i386 -cdrom exylus.iso

clean:
	find -type f \( -name "*.o" -o -name "*.bin" \) -delete
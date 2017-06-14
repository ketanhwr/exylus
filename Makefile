AS=/home/ketan/opt/cross/bin/i686-elf-as
CC=/home/ketan/opt/cross/bin/i686-elf-gcc

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

all:
	$(AS) boot.s -o boot.o
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o
	$(CC) -T linker.ld -o exylus.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

run:
	qemu-system-i386 -kernel exylus.bin

clean:
	find -type f \( -name "*.o" -o -name "*.bin" \) -delete
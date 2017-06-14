#include "vga.h"

void kernel_main ()
{
	terminal_initialize();
	terminal_writestring("Exylus..!\n");
}

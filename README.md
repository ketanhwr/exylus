# Exylus

Exylus is a hobby operating system which I'm writing because I'm bored and want a massive project to take up all the time from my next few semesters. The kernel is multiboot compliant and can be boot up using GNU GRUB.

![Screenshot](https://image.ibb.co/dKCDDQ/exylus.png)

## Build Instructions

1. Setup a GCC Cross Compiler. Go through this link regarding the process: [http://wiki.osdev.org/GCC_Cross-Compiler](http://wiki.osdev.org/GCC_Cross-Compiler)

2. Install `make` and QEMU emulator (this is required to run the operating system).

3. Modify the `Makefile` and change the values of `AS` and `CC` to point to your locally setup cross-compiler.

4. Compile the source code.
	```
	$ make
	```

5. Run the operating system.
	```
	$ make run
	```

### Generating ISO (thanks to doztrock)

1. After follwing the above instructions, do
	```
	$ make iso
	```
2. And run the iso with
	```
	$ make run-iso
	```

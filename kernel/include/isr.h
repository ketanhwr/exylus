/*
 * isr.h
 *
 * This file is a part of Exylus.
 */

#include "system.h"

void isr_handler(registers_t *regs);

void isr_install_handler(int32_t isr, void (*handler)(registers_t *r));

void isr_uninstall_handler(int32_t isr);

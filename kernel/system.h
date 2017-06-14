/*
 * system.h
 * Copyright 2017, Ketan Gupta <ketan19972010@gmail.com>
 *
 * This file is a part of Exylus.
 */

#pragma once

#include <stdint.h>

void outb (uint16_t port, uint8_t val);

uint8_t inb(uint16_t port);

#pragma once

#include <stdbool.h>

#define EXCEPTION_WADDERR       0x100
#define EXCEPTION_RADDERR       0x0E0

extern volatile bool address_exception;

void setup_exception_handling();


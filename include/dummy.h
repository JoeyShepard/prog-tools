#pragma once

#include <stdint.h>
#include "structs.h"

int text_editor(int command_ID, struct WindowInfo *windows, int selected_window);
int python(int command_ID, struct WindowInfo *windows, int selected_window);
int emu_msp430(int command_ID, struct WindowInfo *windows, int selected_window);
int emu_6502(int command_ID, struct WindowInfo *windows, int selected_window);
int help(int command_ID, struct WindowInfo *windows, int selected_window);


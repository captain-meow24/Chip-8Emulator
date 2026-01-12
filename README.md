# Chip-8Emulator

Chip-8 is a simple processor with sixteen 8-bit registers and 4KB of memory.
Chip-8 actually never existed as a real processor and only as an interpreter that could run many simple games.
It has a 16 level stack to keep track of function calls, whenever a function is called, the PC address of the next instruction without the function call (PC+2 byte) is pushed onto the stack and the top address is popped when a function returns.
I used Tigr to render display, it make complex visual patterns and animations possible within the constaint of a 62x32 pixel monochrome display (baby pink for backgroun and black for sprites).

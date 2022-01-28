#include "types.h"
#include "gdt.h"

void print(char* str, int clr, int x, int y) {
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;
	
	int offset = y * 80 + x;
	for(int i = 0; str[i] != '\0'; ++i) {
		VideoMemory[i+offset] = (VideoMemory[i+offset] & clr) | str[i];
	}
}

typedef void(*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
	for(constructor* i = &start_ctors; i != &end_ctors; i++) {
		(*i)();
	}
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
	print("Kernel test", 0xFF00, 0, 0);
	print("Hei", 0x5500, 0, 1);
	print("Fler", 0xFF00, 0, 2);
	print("farget tekst", 0x5500, 4, 2);
	print("> ", 0xFF00, 0, 4);

	GlobalDescriptorTable gdt;
	
	while(1);
}

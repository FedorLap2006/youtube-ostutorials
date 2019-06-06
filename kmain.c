#include <yot/stdtypes.h>

unsigned short *videoMemory = (unsigned short*)0xb8000;
void print_str(char* str) {

  for (int i = 0; str[i] != '\0'; i++) {
    videoMemory[i] = (videoMemory[i] & 0xFF00) | str[i];
  }

}



struct multiboot_information {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	const char *cmdline;
};

void kmain(int magic, struct multiboot_information *boot_ptr) {
	print_str("hello world!");
}

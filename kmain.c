#include <yot/stdtypes.h>
#include <yot/console.h>

extern unsigned short *video_memory;
void print_str(char* str) {

  for (int i = 0; str[i] != '\0'; i++) {
    video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
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
	cls();
	console_setcolor(BLUE,CYAN);
	printf("    Copyright (C) %d  %s \n \
\n\
    This program is free software: you can redistribute it and/or modify \n \
    it under the terms of the GNU General Public License as published by \n \
    the Free Software Foundation, either version 3 of the License, or \n \
    (at your option) any later version. \n \
\n\
    This program is distributed in the hope that it will be useful, \n \
    but WITHOUT ANY WARRANTY; without even the implied warranty of \n \
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \n \
    GNU General Public License for more details. \n \
\n\
    You should have received a copy of the GNU General Public License \n \
    along with this program.  If not, see <https://www.gnu.org/licenses/>.",2019,"LifeArea (C)");
}

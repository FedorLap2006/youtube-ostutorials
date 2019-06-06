#include <depthos/console.h>
#include <depthos/ports.h>
#include <depthos/stdarg.h>

unsigned short *video_memory = (unsigned short *)0x000B8000;
char tab_width = 8; // Размер табуляции
short cursor_pos = 0; // Позиция курсора на экране
short console_color = 0x0F00; // Цвет фона и символа печатаемого на экране

// Устанавливает цвет печатаемых символов и цвет их фона
void console_setcolor(char background_color, char char_color){
	console_color = background_color;
	console_color <<= 4;
	console_color |= char_color;
	console_color <<= 8;
}

// Очищает консоль
void cls(){
	short i = CONSOLE_SIZE;
	int a = 0;
	while(i--)
		video_memory[a++] = console_color | ' ';
	set_cursor_pos(0);
}

// Прокрутка текста на одну строку
void console_move_up(){
	short i;
	short a = 0;
	short b = CONSOLE_WIDTH;
	i = CONSOLE_SIZE - CONSOLE_WIDTH;
	// Сначала текст перемещается на одну строку вверх, удаляя первую строку
	while(i--)
		video_memory[a++] = video_memory[b++];
	i = CONSOLE_WIDTH;
	// А затем последняя строка заполняется пробелами
	while(i--)
		video_memory[a++] = console_color | ' ';
	set_cursor_pos(cursor_pos - CONSOLE_WIDTH);
}

// Устанавливает новую позицию курсора
void set_cursor_pos(short pos){
	cursor_pos = pos < 0 ? 0 : pos;
	outb(0x3D4, 14);
	outb(0x3D5, cursor_pos >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursor_pos);
}

// Печататет простой текст на экране
void print_text(const char *s){
	short last_line = CONSOLE_SIZE - 1; // Позиция, определяющая необходимость прокрутки текста
	short err_stop = CONSOLE_MAX_OUTPUT_SIZE; // На случай, если будет подана строка без нуль-терминатора

	while(err_stop--){
		// Если символ не поместится на экране, то освободить последнюю строку
		if(cursor_pos > last_line)
			console_move_up();
		// Если вся строка была напечатана
		if(*s == '\0'){
			set_cursor_pos(cursor_pos);
			return;
		}
		// Переход на новую строку
		if(*s == '\n'){
			cursor_pos = cursor_pos / CONSOLE_WIDTH + 1;
			cursor_pos = cursor_pos * CONSOLE_WIDTH;
			s++;
			continue;
		}
		// Табуляция
		if(*s == '\t'){
			cursor_pos += tab_width - cursor_pos % tab_width;
			s++;
			continue;
		}
		// Вывод символа на экран
		video_memory[cursor_pos] = console_color | *s;
		cursor_pos++;
		s++;
	}
}

// Печатает целое число на экране
void print_integer(unsigned int n){
	char buffer[11];
	short i = 10;

	buffer[i] = 0;
	do{
		i--;
		buffer[i] = n % 10 + 48;
		n = n / 10;
	}while(n && i);
	print_text(&buffer[i]);
}

// Форматированный вывод текста на экран
void printf(const char *formated_string, ...){
	short last_line = CONSOLE_SIZE - 1; // Позиция, определяющая необходимость прокрутки текста
	short err_stop = CONSOLE_MAX_OUTPUT_SIZE; // На случай, если будет подана строка без нуль-терминатора
	char *s = (char *)formated_string;
	int buffer_int;
	va_list ap;
	va_start(ap, formated_string);

	while(err_stop--){
		// Если символ не поместится на экране, то освободить последнюю строку
		if(cursor_pos > last_line){
			console_move_up();
			cursor_pos -= CONSOLE_WIDTH;
		}
		// Если вся строка была напечатана
		if(*s == '\0'){
			set_cursor_pos(cursor_pos);
			return;
		}
		// Переход на новую строку
		if(*s == '\n'){
			cursor_pos = cursor_pos / CONSOLE_WIDTH + 1;
			cursor_pos = cursor_pos * CONSOLE_WIDTH;
			s++;
			continue;
		}
		// Табуляция
		if(*s == '\t'){
			cursor_pos += tab_width - cursor_pos % tab_width;
			s++;
			continue;
		}
		// Обработка параметра в строке
		if(*s == '%'){
			s++;
			switch(*s){
				case 'd':
					buffer_int = va_arg(ap, int);
					if(buffer_int < 0){
						video_memory[cursor_pos++] = console_color | '-';
						buffer_int = -buffer_int;
					}
					print_integer(buffer_int);
					break;
				case '%':
					video_memory[cursor_pos++] = console_color | *s;
					break;
				case 's':
					print_text(va_arg(ap, char*));
					break;
			}
			s++;
			continue;
		}
		// Вывод символа на экран
		video_memory[cursor_pos] = console_color | *s;
		cursor_pos++;
		s++;
	}
	va_end(ap);
}


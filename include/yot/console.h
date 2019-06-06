#pragma once



#define BLACK		0x00
#define DARK_BLUE	0x01
#define DARK_GREEN	0x02
#define DARK_CYAN	0x03
#define DARK_RED	0x04
#define DARK_MAGNETA	0x05
#define DARK_YELLOW	0x06
#define GRAY		0x07
#define DARK_GRAY	0x08
#define BLUE		0x09
#define GREEN		0x0A
#define CYAN		0x0B
#define RED		0x0C
#define MAGNETA		0x0D
#define YELLOW		0x0E
#define WHITE		0x0F



#define CONSOLE_WIDTH 80 // Ширина экрана в символах
#define CONSOLE_HEIGHT 25 // Высота экрана в символах
#define CONSOLE_SIZE (CONSOLE_WIDTH * CONSOLE_HEIGHT) // Сколько символов может поместиться на экране
#define CONSOLE_MAX_OUTPUT_SIZE 500 // Для предотвращения бесконечной печати текста



void console_setcolor(char background_color, char char_color);
void cls();
void set_cursor_pos(short pos);
void printf(const char *formated_string, ...);

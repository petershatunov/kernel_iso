#include <stdint.h>
#include <stddef.h>

uint16_t* video = (uint16_t*)(0xB8000);
size_t terminal_row = 0;
size_t terminal_col = 0;

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 20;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

// const int COLOR_BLACK = 0x00;
// const int COLOR_WHITE = 0x0F;

//void init_screen();
// void print_chars(char* str);
//uint16_t vga_entry(unsigned char c, uint8_t color);


uint8_t vga_entry_color(uint8_t fg, uint8_t bg) 
{
	return fg | bg << 4;
}

uint16_t vga_entry(unsigned char c, uint8_t color)
{
    // return (uint16_t) c | (uint16_t) (color << 8);
    return c | (color << 8);
}

void terminal_putchar(size_t x, size_t y, char c, char color)
{
    video[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void terminal_writechar(char c, char color)
{
    if (c == '\n')
    {
        terminal_row++;
        terminal_col = 0;
        return;
    } 
    terminal_putchar(terminal_col, terminal_row, c, color);
    if (++terminal_col == VGA_WIDTH) {
        terminal_col = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void print(const char* data)
{
    for(size_t i = 0; i < strlen(data); i++)
        terminal_writechar(data[i], 15);
}

void init_screen()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            if (y > 5 && y % 2) continue;
            uint8_t terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_LIGHT_BLUE);
            terminal_putchar(x, y, ' ', terminal_color);
        }
    }
}

void main()
{
    init_screen();
    print("Hello\nWorld\nAnd\nMicrokernel!");
}

// void clear_screen()
// {
//     volatile unsigned char *video = (unsigned char *)videoAddress;
//     int i = 0;
//     while(i < LINE_ROWS * LINE_LENGTH * 2) {
//         video[i] = ' ';
//         video[i+1] = COLOR_BLACK;
//         i += 2;
//     }
// }

// void print_chars(char* str)
// {
//     unsigned char *video = (unsigned char *)videoAddress;
//     int j = 0;
//     for (size_t i = 1; 1; i+=2) {
//         char character = str[j++];
//         if (character == '\0') {
//             return;
//         }
//         video[i] = character;
//     }
// }


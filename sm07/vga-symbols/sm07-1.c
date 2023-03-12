#include "drivers/vga.h"

void show_vga_symbol_table(void){
	vga_clear_screen();
    unsigned int row = 0, col = 0;
    vga_set_char(0, ' ');
    col = 1;
    for (int i = 0; i < 16; ++i) {
        vga_set_char(col, ' ');
        if (i < 10) {
            vga_set_char(col + 1, (char) ('0' + i));
        } else {
            vga_set_char(col + 1, (char) ('a' + i - 10));
        }
        col += 2;
    }
    for (int i = 0; i < 16; ++i) {
        ++row;
        if (i < 10) {
            vga_set_char(row * COLS, (char) ('0' + i));
        } else {
            vga_set_char(row * COLS, (char) ('a' + i - 10));
        }
        col = 1;
        for (int j = 0; j < 16; ++j) {
            vga_set_char(row * COLS + col, ' ');
            vga_set_char(row * COLS + col + 1, (char) (i * 16 + j));
            col += 2;
        }
    }
}

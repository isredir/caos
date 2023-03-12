#include "drivers/port.h"
#include "drivers/vga.h"

void vga_set_cursor(unsigned offset) {
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, offset >> 8);
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, offset & ((1 << 8) - 1));
}

void vga_putc(char c) {
    unsigned offset = vga_get_cursor();
    if (c == '\n') {
        unsigned row = offset / COLS;
        offset = (row + 1) * COLS;
    } else {
        vga_set_char(offset, c);
        ++offset;
    }
    if (offset == ROWS * COLS) {
        offset -= COLS;
        for (int i = 0; i < ROWS - 1; ++i) {
            for (int j = 0; j < COLS; ++j) {
                vga_set_char(i * COLS + j,
                             video_memory[2 * (i * COLS + j + COLS)]);
            }
        }
        for (int j = 0; j < COLS; ++j) {
            vga_set_char((ROWS - 1) * COLS + j, ' ');
        }
    }
    vga_set_cursor(offset);
}

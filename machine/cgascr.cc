/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* This class allows accessing the PC's screen.  Accesses work directly on   */
/* the hardware level, i.e. via the video memory and the graphic adapter's   */
/* I/O ports.                                                                */
/*****************************************************************************/

#include "machine/cgascr.h"
#include <cstddef>

/* Add your code here */ 
char* const CGA_Screen::CGA_START = (char *)0xb8000;

void CGA_Screen::show (int x, int y, char c, unsigned char attrib)
{
    char *pos;

    //assert(x >= 0 && x < COLS_COUNT);
    //assert(y >=0 && y < ROW_COUNT);

    pos = CGA_START + 2 * (x + y * COLS_COUNT);
    *pos = c;
    *(pos + 1) = attrib;
}


void CGA_Screen::setpos (int x, int y)
{
    IO_Port index_reg(INDEXREGISTER);
    IO_Port data_reg(DATENREGISTER);

    unsigned short cursor_location = y * COLS_COUNT + x;

    // cursor LOW port to vga INDEX register
    index_reg.outb(REG_INX_CURSOR_LOW);
    data_reg.outb((unsigned char)(cursor_location & 0xFF));

    // cursor HIGH port to vga INDEX register
    index_reg.outb(REG_INX_CURSOR_HIGH);
    data_reg.outb((unsigned char)(cursor_location >> 8) & 0XFF);
} 


void CGA_Screen::getpos (int &x, int &y)
{
    IO_Port index_reg(INDEXREGISTER);
    IO_Port data_reg(DATENREGISTER);
    unsigned short pos = 0;

    // get REG_INX_CURSOR_HIGH
    index_reg.outb(REG_INX_CURSOR_HIGH);
    pos = data_reg.inb() << 8;

    // get REG_INX_CURSOR_LOW
    index_reg.outb(REG_INX_CURSOR_LOW);
    pos |= data_reg.inb();

    x = pos % COLS_COUNT;
    y = pos / COLS_COUNT;
    
    //assert((pos - x) % COLS_COUNT == 0);

}



void CGA_Screen::print (char* text, int length, unsigned char attrib)
{
    int x, y;
    getpos(x, y);

    for (int i = 0; i != length; ++i) {
        // '\n' case.
        if (text[i] == '\n') {
            ++y;
            x = 0;
        } else {
            // output 1 character .
            show(x, y, text[i], attrib);
            ++x;
        }
 
        // When we reach the end of a line => go to next line
        if (x >= COLS_COUNT) {
            ++y;
            x = 0;
        }
 
        // When we reach the end of the screen, we should scroll up each line in screen by 1 line
        if (y >= ROW_COUNT) {
            // Copy all CGA memory up one line.
            for (int i = 0; i != 2 * COLS_COUNT * (ROW_COUNT - 1); ++i)
                CGA_START[i] = CGA_START[i + (2 * COLS_COUNT)];
            // Zero out last line.
            for (int i = 2 * COLS_COUNT * (ROW_COUNT - 1); i != 2 * COLS_COUNT * ROW_COUNT; i += 2) {
                CGA_START[i] = ' ';
	            CGA_START[i+1] = 0x0f;
            }

            y = ROW_COUNT - 1;
        }
    }

    setpos(x, y);
} 

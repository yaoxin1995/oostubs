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
#include "machine/io_port.h"
#include <cstddef>


char* const CGA_Screen::CGA_START = (char *)0xb8000;

CGA_Screen::CGA_Screen()
{

}

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


void memcpy(void * dest, const void * source, size_t num)
{
	for(int i = 0; i < num; i++) 
	{
		*((char*)dest+i) = *((char*)source+i);
	}
}

void CGA_Screen::shift_up_one_line ()
{
    char *dest, *source, *pos;

    for (int i = 0; i < ROW_COUNT - 1; i++) {
        dest = CGA_START + i * COLS_COUNT * 2;
        source = CGA_START + (i + 1) * COLS_COUNT * 2;
        memcpy(dest, source, COLS_COUNT * 2);
    }

    pos = CGA_START + 2 * COLS_COUNT * (ROW_COUNT - 1);   
    for (int i = 0; i < COLS_COUNT - 1; i++) 
        pos[i * 2] = ' ';
    
}

void CGA_Screen::print (char* text, int length, unsigned char attrib)
{
    int start_x, start_y, i;

    getpos(start_x, start_y);

    for (i = 0; i < length; i++) {
        if (text[i] == '\n') {
            if (start_y == COLS_COUNT -1)
                shift_up_one_line();
            else
                start_y += 1;
            start_x = 0;
            continue;
        }

        show(start_x, start_y, text[i], attrib);

        if (start_x == COLS_COUNT - 1) {
            start_x = 0;
            if (start_y == ROW_COUNT - 1)
                shift_up_one_line();
            else
                start_y++;
        }
        start_x++;

    }

    setpos(start_x, start_y);

} 




	
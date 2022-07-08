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


void memcpy(void * dest, const void * source, size_t num)
{
	for(size_t i = 0; i < num; i++) 
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
    
 int x, y;
  getpos(x, y);

  for (int i = 0; i != length; ++i) {
    // '\n' behandeln.
    if (text[i] == '\n') {
      ++y;
      x = 0;
    } else {
      // 1 Zeichen ausgeben.
      show(x, y, text[i], attrib);
      ++x;
    }

    // Wenn das Ende der Zeile erreicht ist umbrechen.
    if (x >= 80) {
      ++y;
      x = 0;
    }

    // Wenn das Ende des Bildschirms erreicht ist nach oben scrollen.
    if (y >= 25) {
      // Gesamten CGA-Speicher eine Zeile nach oben kopieren.
      for (int i = 0; i != 2 * 80 * 24; ++i)
        CGA_START[i] = CGA_START[i + (2 * 80)];
      // Letzte Zeile ausnullen.
      for (int i = 2 * 80 * 24; i != 2 * 80 * 25; i += 2) {
        CGA_START[i] = ' ';
	CGA_START[i+1] = 0x0f;
      }
      y = 24;
    }
  }

  setpos(x, y);
    
} 

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

extern "C" {
  // Get declaration for f(int i, char c, float x)
  #include "clibs.h"
}


/* Add your code here */ 

CGA_Screen::CGA_Screen()
{
    CGA_START = (char *)0xb8000;
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

/**
 * @brief set curse postion
 * Registers 14 and 15 set the cursor address, which is calculated from the cursor position. 
 * For example, to place the cursor in row 10 and column 63, calculate 10 * 80 + 63 = 863. 
 * This value is then written into the high and low bytes of the cursor address registers
 * @param x 
 * @param y 
 * @return ** void 
 */
void CGA_Screen::setpos (int x, int y)
{
    unsigned short cursor_loc = y * COLS_COUNT + x;

    // cursor LOW port to vga INDEX register
    outb(IDXPORT, REG_INX_CURSOR_LOW);
    outb(DATAPORT, (unsigned char)(cursor_loc & 0xFF));

    // cursor HIGH port to vga INDEX register
    outb(IDXPORT, REG_INX_CURSOR_HIGH);
    outb(DATAPORT, (unsigned char)(cursor_loc >> 8) & 0XFF);
}


/**
 * @brief get curse position
 * 
 * @param x 
 * @param y 
 */

void CGA_Screen::getpos (int &x, int &y)
{
    int pos;

    // get REG_INX_CURSOR_HIGH
    outb(IDXPORT, REG_INX_CURSOR_HIGH);
    pos = inb(DATAPORT) << 8;

    // get REG_INX_CURSOR_LOW
    outb(IDXPORT, REG_INX_CURSOR_LOW);
    pos |= inb(DATAPORT);

    x = pos % COLS_COUNT;
    y = (pos - x) / COLS_COUNT;
    
    //assert((pos - x) % COLS_COUNT == 0);

}

void CGA_Screen::shift_up_one_line (int &x, int &y)
{
    //shift up
    my_memmove(CGA_START, CGA_START + COLS_COUNT, sizeof(CGA_START[0]) * (ROW_COUNT - 1) * COLS_COUNT);
    // delete the last line
    my_memset(CGA_START + COLS_COUNT * (ROW_COUNT - 1), '0', COLS_COUNT);

    x = 0;
    y = ROW_COUNT - 1;
}

void CGA_Screen::print (char* text, int length, unsigned char attrib)
{
    int start_x, start_y, i;

    getpos(start_x, start_y);

    //assert(start_x >=0 && start_x < COLS_COUNT);
    //assert(start_y >=0 && start_y < ROW_COUNT);

    for (i = 0; i < length; i++) {
        if (*text == '\n') {
            if (start_y == COLS_COUNT -1)
                shift_up_one_line(start_x, start_y);
            else {
                start_x = 0;
                start_y += 1;
            }
            text++;
        }

        show(start_x, start_y, *text, attrib);

        text++;

        if (start_x == COLS_COUNT - 1 && start_y == ROW_COUNT -1)
            shift_up_one_line(start_x, start_y);
        else {
            start_x++;
            if (start_x == COLS_COUNT) {
                start_y++;
                start_x = 0;
            }
        }
    }

    setpos(start_x, start_y);
}
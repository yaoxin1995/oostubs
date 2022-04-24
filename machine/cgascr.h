#ifndef __screen_include__
#define __screen_include__

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


#include "machine/io_port.h"


#define REG_INX_CURSOR_LOW 15
#define REG_INX_CURSOR_HIGH 14

#define COLS_COUNT 80
#define ROW_COUNT 25

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA  5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define HELLCYAN 11
#define BRIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15

#define FOREGROUND_COLOR_SHIFT 0
#define BACKGROUND_COLOR_SHIFT 4
#define FLASH_SHIFT 7

#define DEFAULT_ATTRIBUTES_WITH_BLINK (WHITE << FOREGROUND_COLOR_SHIFT | BLACK << BACKGROUND_COLOR_SHIFT | 1 << FLASH_SHIFT)
#define DEFAULT_ATTRIBUTES_WITHOUT_BLINK (WHITE << FOREGROUND_COLOR_SHIFT | BLACK << BACKGROUND_COLOR_SHIFT | 0 << FLASH_SHIFT)

class CGA_Screen {
private:
/* Add your code here */

	CGA_Screen(const CGA_Screen &copy); // prevent copying

  /**
   * Method shift_up_one_line() scrolls the screen one row up. 
   * The new row at the bottom of the screen has to be empty (filled with spaces).
   */
	void shift_up_one_line ();

  /**
   * Method show() displays a character at a given position using the 
   * specified attributs.
   *
   * @param x column number of display position
   * @param y row number of display position
   * @param character character to be displayed
   * @param attrib display attributs
   */
	void show (int x, int y, char c, unsigned char attrib);

  /**
   * Method setpos() sets a new position for the screen cursor.
   *
   * @param x column number of new position 
   * @param y row number of new position
   */
	void setpos (int x, int y);

  /**
   * Method getpos() gets the current position of the screen cursor.
   *
   * @param x reference for column number of current position
   * @param y reference for row number of curent position
   */
	void getpos (int &x, int &y);

protected:
	// initialize static const member only possible for int types
	static const int INDEXREGISTER = 0x3d4;
	static const int DATENREGISTER = 0x3d5;

	static char* const CGA_START; // can't be initialized here
public:

	CGA_Screen();
	void print (char* text, int length, unsigned char attrib);
};

#endif
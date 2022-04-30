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

#define DEFAULT_ATTRIBUTES (WHITE << FOREGROUND_COLOR_SHIFT | BLACK << BACKGROUND_COLOR_SHIFT | 1 << FLASH_SHIFT)


class CGA_Screen {
private:
/* Add your code here */
 	IO_Port index_reg;
	IO_Port data_reg;
	// initialize static const member only possible for int types
	static const int INDEXREGISTER = 0x3d4;
	static const int DATENREGISTER = 0x3d5;

	static char* const CGA_START; // can't be initialized here

	CGA_Screen(const CGA_Screen &copy); // prevent copying
	void shift_up_one_line ();


public:
	CGA_Screen(): index_reg(INDEXREGISTER), data_reg(DATENREGISTER)
/* Add your code here */ 
{}

/* Add your code here */ 
void show(int x, int y, char c, unsigned char attrib);

void setpos(int x, int y);

void getpos(int &x, int &y);

 void print(char *text, int length, unsigned char attrib);

};

#endif
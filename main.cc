/* Add your code here */ 
#include "machine/cgascr.h"

#define TEXTLEN 100


static void get_string(char* str, int size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size) {
        --size;
        for (int n = 0; n < size; n++) {
            int key = n % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
    }

}



int main()
{
/* Add your code here */
	CGA_Screen screen;
	char text[TEXTLEN] = {};

	get_string(text, TEXTLEN);

	screen.print(text, TEXTLEN, DEFAULT_ATTRIBUTES);



 
/* Add your code here */ 
 
/* Add your code here */ 
 
	return 0;
}

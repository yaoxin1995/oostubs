/* Add your code here */ 
#include "machine/cgascr.h"
#include "device/cgastr.h"

#define TEXTLEN 1000


static void get_string(char* str, int size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...\n\n";
    if (size) {
        --size;
        for (int n = 0; n < size; n++) {
            int key = n % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
    }

}


static void test_sga_screen() 
{
	CGA_Screen screen;
	char text[TEXTLEN] = {};

	get_string(text, TEXTLEN);

	screen.print(text, TEXTLEN, DEFAULT_ATTRIBUTES);
}

/**
 * 
 * 
 * char: smallest addressable unit of the machine that can contain basic character set
 * unsigned char : [0:255]
 * unsigned short:  [0, 65,535] 
 * short : [−32,767, +32,767]
 * unsigned int: [0, 65,535]
 * int: [−32,767, +32,767]
 * unsigned long:  [0, 4,294,967,295]
 * long 
 */

static void test_cga_Stream()
{
	CGA_Stream cout;

	char char_value = 'a';
	unsigned char unsigned_char_value = 254;
	unsigned short unsigned_short_value = 40000;
	short short_value = 20000;
	unsigned int unsigned_int_value = 40000;
	int int_value = -11111;
	unsigned long unsigned_long_value = 500000;
	long long_value = -20000;

	int *pointer = (int *)0x111;

	//print unsigned char c
	cout << "this is char value: " << char_value << endl;

	cout << "this is unsigned char value: " << unsigned_char_value << endl;

	cout << "this is unsigned short value: " << unsigned_short_value << endl;

	cout << "this is short value: " <<  short_value << endl;

	cout << "this is unsigned int value: " << unsigned_int_value << endl;

	cout << "this is int value: " << int_value << endl;

	cout << "this is unsigned long: " << unsigned_long_value << endl;

	cout << "this is long value: " << long_value << endl;

	cout << "this pointer value (0x111): " << pointer << endl;


	cout << "changed the base to binary and print the value 10: " << bin << 10;

	cout << "changed the base to octar and print the value 10: " << oct << 10;

	cout << "changed the base to dec and print the value 10: " << dec << 10;

	cout << "changed the base to hex and print the value 10: " << oct << 10;


}


int main()
{
/* Add your code here */
	test_sga_screen();
 
/* Add your code here */ 

	test_cga_Stream();
 
/* Add your code here */ 
 
	return 0;
}

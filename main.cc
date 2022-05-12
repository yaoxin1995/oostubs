
#include "machine/cgascr.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"

#include "device/keyboard.h"
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "user/appl.h"
#include "guard/secure.h"





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


	cout << "changed the base to binary and print the value 10: " << bin << 10 << endl;

	cout << "changed the base to octar and print the value 10: " << oct << 10 << endl;

	cout << "changed the base to dec and print the value 10: " << dec << 10 << endl;

	cout << "changed the base to hex and print the value 10: " << hex << 10 << endl;



}

static void test_key_ctrl(){
	CGA_Stream cout;
    Keyboard_Controller kctrl;
    Key key;
	char a;

	kctrl.set_led(1, 1);
	kctrl.set_led(2, 1);
	kctrl.set_led(4, 1);
    kctrl.set_repeat_rate(20, 3);
	while(true){

		key = kctrl.key_hit();
		if (key.valid()) {
			a = key.ascii();
			cout << a << " ";
			cout.flush();
		}
	}
}

Plugbox plugbox;
PIC pic;
CGA_Stream cout;
Panic panic;
CPU cpu;
Keyboard keyboard;
Application application;
Guard guard;

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	application.action();
	for(;;);
 
	return 0;
}

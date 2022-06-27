
#include "machine/cgascr.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"

#include "device/keyboard.h"
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "user/appl.h"
#include "guard/secure.h"
#include "thread/scheduler.h"
#include "device/watch.h"
#include "syscall/guarded_scheduler.h"



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
// Scheduler scheduler;
Guarded_Scheduler scheduler;
Guard guard;
Watch watch(1000);

static char app_stack[2048];

int main()
{
	cpu.enable_int();  
	keyboard.plugin();
	/*The constructor gives the application process a stack. 
	Here tos must already point to the end of the stack, since 
	for the PC stacks grow from the high to the low addresses.
	*/
	Application application(app_stack + sizeof(app_stack));

	cout << "start ...." << endl;                      
	scheduler.ready(application);
	/*
	Q: 如果将 guard.enter(); 和 watch.windup(); 交换 会发生什么?
	1. toc_switch 中 modify the address which is not belonging to it
	2. 更严重是会enqueue null pointer 到 thread ready list 中,下一次会 call resume() 时 会从 ready list 中dequeue null pointer,导致scheduler无法 切换进程 see 
	https://github.com/yaoxin1995/oostubs/blob/shiyue-task5/thread/scheduler.cc#L50
	*/
	guard.enter();	 // application is the very first thread, scheduler lauch this thread by call kickoff fucntion. In kickoff, we leave the critical section, which means we have to enter critical section here 		
	watch.windup();  
	

	scheduler.schedule();

	for(;;){
			cout.setpos(40, 20); 
            cout << "II am stucked" << endl;
	}
	return 0;
}

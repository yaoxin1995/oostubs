/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Handles timer interrupts by managing a time slice and triggering a        */
/* process switch if necessary.                                              */
/*****************************************************************************/

#ifndef __speaker_include__
#define __speaker_include__

/* INCLUDES */

#include "machine/pit.h"
#include "device/cgastr.h"
#include "syscall/guarded_buzzer.h"
#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_buzzer.h"
#include "device/watch.h"
#include "machine/pit.h"
 
extern CGA_Stream cout; 
extern Guarded_Semaphore semaphore;


class Speaker {
private:
	Speaker(const Speaker &copy); // prevent copying
public:
	Speaker(){};
	 //Play sound using built in speaker
    void play_sound(int nFrequence){
			int Div;
			int tmp;
		
				//Set the PIT to the desired frequency
			Div = 1193180 / nFrequence;
			//0xb6 = 10 11 011 0
			// 1 0 = Channel 2
			// 1 1 = Access mode: lobyte/hibyte
			// 0 1 1 = Mode 3 (square wave generator)
			// 0 = 16-bit binary,

			outb(0x43, 0xb6);
			outb(0x42, (Div)& 0xff );
			outb(0x42,  (Div >> 8));
		
			//And play the sound using the PC speaker
			tmp = inb(0x61);
			if (tmp != (tmp | 3)) {
				outb(0x61, tmp | 3);
 			}
//		cout<<"playing through PIT"<< endl;

	}
 
 //make it shutup
  void nosound() {
 	int tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
	play_sound(1000);

 	nosound();
	//set_PIT_2(old_frequency);
	PIT pit(10000);
	

 }

};

#endif

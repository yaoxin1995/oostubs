/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Keyboard driver.                                                          */
/*****************************************************************************/

#include "keyboard.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "device/cgastr.h"


extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream cout;

Keyboard::Keyboard() : read_key(true), sem_key(0) {
}

void Keyboard::plugin (){

    plugbox.assign(Plugbox::keyboard, *this); //keyboard object register with the plugbox
    pic.allow(PIC::keyboard);  //pic allow keyboard interrupt

}

bool Keyboard::prologue(){

	Key key = key_hit();

    if(key.ascii()!=0){
		last_key = key;
		return true;
	} else if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del) {
		reboot();
	}
    return false;
}

void Keyboard::epilogue(){
    // read_key is used for "If a buffer entry has to be overwritten without the 
    // old value having been fetched by an application process, the semaphore must 
    // therefore not be incremented"  ==> because the key buffer size is 1, therefore we 
    // use read_key variable to make sure that the max. value of semaphore is 1

    if (read_key) {
        this->read_key = false;
        sem_key.v();
    }
/*
    int x, y;
    cout.flush();
    cout.getpos(x, y);
    cout.setpos(10, 10);
    cout << last_key << endl; 
    cout.flush();
    cout.setpos(x, y);
*/
}


Key Keyboard::getkey() {
  sem_key.p();      //cosuming the key
  read_key = true;
  return last_key;
}
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Keyboard driver.                                                          */
/*****************************************************************************/

#include "device/keyboard.h"
#include "machine/pic.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "guard/guard.h"

extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream cout;
extern Guard guard;

void Keyboard::plugin (){

    plugbox.assign(Plugbox::keyboard, *this); //keyboard object register with the plugbox
    pic.allow(PIC::keyboard);  //pic allow keyboard interrupt

}

bool Keyboard::prologue(){

    if(key.valid()){
        if( key.ctrl() && key.alt() && (key.scancode() == Key::scan::del)) //ctrl + alt + del
            reboot();
        else {
            return true;
        }
    }
    return false;
    
}

void Keyboard::epilogue(){
        int x, y;
        cout.flush();
        cout.getpos(x, y);
        cout.setpos(10, 10);
        cout << key << endl;
        cout.flush();
        cout.setpos(x, y);
}
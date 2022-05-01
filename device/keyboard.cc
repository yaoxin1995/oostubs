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

extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream cout;
extern Panic panic;

void Keyboard::plugin (){

    plugbox.assign(Plugbox::keyboard, *this); //keyboard object register with the plugbox
    pic.allow(PIC::keyboard);  //pic allow keyboard interrupt

}

void Keyboard::trigger(){
    int x, y;
    Key key = key_hit();

    if(key.valid()){
        if( key.ctrl() && key.alt() && (key.scancode() == Key::scan::del))
            reboot();
        else{
            cout.flush();
            cout.getpos(x, y);
            cout.setpos(10, 10);
            cout << key << endl;
            cout.flush();
            cout.setpos(x, y);
        }
    }
}
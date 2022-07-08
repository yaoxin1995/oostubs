/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S P E A K E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Semaphore class implements the system call interface to the   */
/* Semaphore class.                                                          */
/*****************************************************************************/

#ifndef __Guarded_Speaker_include__
#define __Guarded_Speaker_include__

/* Add your code here */ 
#include "machine/speaker.h"
#include "guard/secure.h"

class Guarded_Speaker : public Speaker
/* Add your code here */ 
{
private:
	Guarded_Speaker(const Speaker &copy); // prevent copying
public:
    Guarded_Speaker() : Speaker() {}
    void play_sound(int nFrequence) {
        Secure s;
        Speaker::play_sound(nFrequence);

    }

    void nosound() {
        Secure s;
        Speaker::nosound();
    }

    void beep() {
        Secure s;
        Speaker::beep();
    }
 
};

#endif

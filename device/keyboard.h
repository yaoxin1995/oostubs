/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Keyboard driver.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/plugbox.h"
#include "machine/pic.h"
#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"
#include "device/cgastr.h"
#include "meeting/semaphore.h"


class Keyboard :  public Gate, public Keyboard_Controller

{
private:
	Keyboard(const Keyboard &copy); // prevent copying
	Key last_key;	//shared charakter between prologue and epilogue
	bool read_key;
	Semaphore sem_key;
public:
	Keyboard();
	// PLUGIN: "Plugs in" the keyboard (driver). From now on, keypresses are handled.
	void plugin();

	bool prologue();
	void epilogue();
	Key getkey();

};

#endif
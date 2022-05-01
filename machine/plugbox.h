/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstracts an interrupt vector table. Allows to configure handler routines */
/* for every hardware and software interrupt and every CPU exception.        */
/*****************************************************************************/

#ifndef __Plugbox_include__
#define __Plugbox_include__

#include "guard/gate.h"
#include "device/panic.h"

class Plugbox {
private:
	Plugbox(const Plugbox &copy); // prevent copying
	Gate* gates[64];

public:
	Plugbox ();
	
	enum { 
		timer = 32, 
		keyboard = 33, 
		printer = 39 
	};

	void assign (unsigned int slot, Gate& gate);

	Gate& report (unsigned int slot);
};

#endif

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Default interrupt handler.                                                */
/*****************************************************************************/

#ifndef __panic_include__
#define __panic_include__

/* INCLUDES */
#include "guard/gate.h"
#include "device/cgastr.h"
#include "machine/cpu.h"


class Panic : public Gate
/* Add your code here */ 
{
private:
	Panic (const Panic &copy); // prevent copying
	
	CPU cpu;
	CGA_Stream cout;

public:
    Panic (){}
	
//this method is used to throw out an error message and stop the cpu
	virtual void trigger() override;

};

#endif

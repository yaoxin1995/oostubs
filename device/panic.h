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

public:
    Panic (){}
	
// Simplest form of interrupt handling: An error message is output and the processor is stopped.
	virtual bool prologue() override;

};

#endif

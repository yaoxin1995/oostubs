/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The system's central interrupt handling routine.                          */
/* The parameter specifies the number of the interrupt that occurred.        */
/*****************************************************************************/

/* INCLUDES */
#include "machine/plugbox.h"
#include "guard/guard.h"

/* FUNCTIONS */

extern "C" void guardian (unsigned int slot);
extern Guard guard;
/* GUARDIAN: Low-level interrupt handling. We will extend this function at */
/*           a later point in time.                                        */

extern Plugbox plugbox;
void guardian (unsigned int slot)
{   
    Gate &gate = plugbox.report(slot);
 
 //prologue() return ture and request it's epilogue  
    if(gate.prologue()){
        guard.relay(&gate);
    };
}

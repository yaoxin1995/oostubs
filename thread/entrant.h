/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            E N T R A N T                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* A coroutine that is managed by the Scheduler.                             */
/*****************************************************************************/

#ifndef __entrant_include__
#define __entrant_include__

#include "thread/coroutine.h"
#include "object/chain.h"
class Entrant : public Coroutine, public Chain

{
private:
	Entrant(const Entrant &copy); // prevent copying
public:
    Entrant(void *tos) : Coroutine(tos) {}
};

#endif
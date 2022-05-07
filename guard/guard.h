/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Using this class, we can synchronize activities with a critical section   */
/* with interrupt handlers that also access this critical section. This      */
/* synchronization takes place along the prologue/epilogue model.            */
/*****************************************************************************/

#ifndef __Guard_include__
#define __Guard_include__

#include "guard/locker.h"
#include "object/queue.h"
#include "guard/gate.h"

/* Add your code here */ 

class Guard : public Locker {
private:
	Guard (const Guard &copy); // prevent copying
	Gate *item;
	Queue queue;
public:
	Guard () {}
	
// With this method, the critical section is left
// and the accumulated epilogues are worked off.
	void leave ();	

//Called by guardian if prologue() returned true
	void relay (Gate* item);
};

#endif

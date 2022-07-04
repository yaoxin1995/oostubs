/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Organizer is a special scheduler that additionally allows processes   */
/* (Customer objects) to wait for events (Waitingroom objects).              */
/*****************************************************************************/

#ifndef __organizer_include__
#define __organizer_include__
/* Add your code here */ 
#include "scheduler.h"
#include "thread/customer.h"
#include "meeting/waitingroom.h"
class Organizer : public Scheduler
/* Add your code here */ 
{
private:
	Organizer(const Organizer &copy); // prevent copying
public:
	Organizer() {}
/* Add your code here */ 
// Blocks the running process and gives the processor to the next ready process. 
//It also records which event (in which waiting room) it is now waiting for.
void block (Customer& customer, Waitingroom& waitingroom);

// This method can be used to wake up a sleeping process, i.e. to put it back on the ready list. 
//It should also be marked that the process is now no longer waiting for an event.
void wakeup (Customer& customer);

// This method allows one process to kill another (that). If the process that is on the ready list, 
//the kill method of the scheduler can be used. If, on the other hand, it is waiting for an event, 
//it must be taken down from its list (i.e. out of the waiting room).
void kill (Customer& that);


};

#endif

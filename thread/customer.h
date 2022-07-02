/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Customer class extends the Entrant class with the ability to record   */
/* and retrieve an event that the process in question is waiting for.        */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "meeting/waitingroom.h"
#include "entrant.h"
#include "object/chain.h"
/* Add your code here */ 
class Waitingroom; // forward decleration
class Customer : public Entrant
/* Add your code here */ 
{
private:
	Customer (const Customer &copy); // prevent copying
 	Waitingroom* room;	
public:
// The constructor passes the tos parameter to the constructor of the base class Entrant.
	Customer (void* tos) : Entrant(tos){
		room = 0; next = 0;
	};
// This method is used to note in the Customer that it is currently waiting for an event in the Waitingroom w.	
	void waiting_in (Waitingroom *w){ room = w;};
// This can be used to determine in which Waitingroom object the customer is registered. 
//A return value of 0 should mean that the process is not waiting for any event, i.e. 
//it is either the currently running process, is on the scheduler's ready list, has already 
//been terminated or has not yet been registered with the scheduler.	
	Waitingroom* waiting_in (){ return room; };

};

#endif

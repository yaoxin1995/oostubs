/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The class Semaphore implements the synchronization concept of the         */
/* counting semaphore.                                                       */
/*****************************************************************************/

#ifndef __Semaphore_include__
#define __Semaphore_include__

#include "meeting/waitingroom.h"


class Semaphore : public Waitingroom
/* Add your code here */ 
{
private:
	Semaphore(const Semaphore &copy); // prevent copying
	int counter;

public:
	// The constructor initializes the semaphore counter with the specified value c.
	Semaphore (int c) : counter(c){};

	// Wait operation: If the semaphore counter is greater than zero, it is decremented by one only. Otherwise, the currently running process (a Customer object) is added to the waiting list and is blocked.
	void p ();

	// Release operation: If there is at least one customer on the waiting list, the first of them will be woken up. Otherwise, the semaphore counter is incremented by one.
	void v ();

	// ensure that the call to wait() and signal() does not cost more 
	// than to p() and v(),  these two methods should be defined as inline.
	// This method is just another name for the method p().
	inline void wait (){ p();};

	// This method is just another name for the method v().
	inline void signal (){ v();};
};

#endif

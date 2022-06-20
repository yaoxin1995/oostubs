/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S C H E D U L E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements the system-call interface to the Scheduler.                    */
/*****************************************************************************/

#ifndef __guarded_scheduler_include__
#define __guarded_scheduler_include__

/* Add your code here */ 
#include "thread/scheduler.h"
#include "syscall/thread.h"

/**
 * @brief The Guarded_Scheduler implements the system 
 * call interface to the Scheduler. The methods it offers are 
 * mapped directly to the methods of the base class, except that 
 * their execution is protected in each case with the help of an 
 * object of the Secure class, and that Thread objects are handled 
 * instead of Entrant objects.
 * 
 */
class Guarded_Scheduler
/* Add your code here */
:public Scheduler
{
private:
	Guarded_Scheduler(const Guarded_Scheduler &copy); // prevent copying
public:
	Guarded_Scheduler () {}
/* Add your code here */ 

	void ready (Thread& that);

	void exit ();

	void kill (Thread& that);

	void resume ();
};

#endif

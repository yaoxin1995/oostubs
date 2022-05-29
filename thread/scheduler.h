/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Scheduler implementation.                                                 */
/*****************************************************************************/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
#include "object/queue.h"

class Entrant;

class Scheduler : public Dispatcher
{
private:
	Scheduler (const Scheduler &copy); // prevent copying
 	Queue ready_list;

public:

	Scheduler() {}

	// This method registers the process that with the scheduler. It is appended to the end of the ready list.
	void ready(Entrant &that);

	// This method starts up scheduling by removing the first process from the ready list and activating it.
	void schedule();

	// With this method a process can terminate itself. The scheduler does not append it again to the end of the ready list. Instead, it removes the first process from the ready list and activates it.
	void exit();

	// With this method a process can terminate another one (that). The process that is simply removed from the ready list and is thereby never scheduled again.
	void kill(Entrant &that);
	
	// This method allows to trigger a context switch without the calling Entrant having to know which other Entrant objects exist in the system, and which of these should be activated. This decision is made by the scheduler using the entries in its ready list. In this system, it shall append the currently running process to the end of the ready list and activate the first one.
	void resume();
 
};

#endif

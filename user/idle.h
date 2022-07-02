/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop is a thread that does nothing else but count upwards and print this  */
/* on the screen. In between, it yields the CPU. The Scheduler then decides  */
/* which thread shall run next.                                              */
/*****************************************************************************/

#ifndef __idle_include__
#define __idle_include__

/* Add your code here */ 
 
#include "device/cgastr.h"
#include "thread/entrant.h"
#include "syscall/thread.h"

class Idle: public Thread
{
private:
	Idle (const Idle &copy); // prevent copying

public:
/* Add your code here */ 
	Idle (void* tos):  Thread(tos){}
	void action ();
};

#endif
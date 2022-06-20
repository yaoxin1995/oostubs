/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K I C K O F F                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Function to start a coroutine.                                            */
/* Since this function is not really called, but only jumped to by a clever  */
/* initialization of the stack of the coroutine, it must never terminate.    */
/* Otherwise a meaningless value would be interpreted as a return address    */
/* and the computer would crash.                                             */
/*****************************************************************************/

/* Add your code here */ 

#include "thread/coroutine.h"
#include "thread/scheduler.h"
#include "guard/guard.h"

extern Scheduler scheduler;
extern Guard guard;
// called with guared lock locked, therefore we need to release the lock

extern "C"  void kickoff (void *dummy1, void *dummy2, void *dummy3, void *dummy4, void *dummy5, void *dummy6, void* object) 
{   
    // Wacht's epilogue calls resume(), which will call kickoff eventually. However Wacht's epilogue is in critical section  and it will never return to it's caller relay()
    // therefore we need to leave the critical section explicitly by calling guard.leave();
    guard.leave();
    Coroutine* obj = (Coroutine *)object;
    obj->action();

    // for(;;){} 
    scheduler.exit();
    
}
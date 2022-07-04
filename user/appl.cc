/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

/* INCLUDES */



#include "user/appl.h"
#include "thread/scheduler.h"
#include "syscall/guarded_scheduler.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"
#include "user/loop.h"

extern Loop loop2;


/* Add your code here */ 
 
/* GLOBAL VARIABLES */

extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
// extern Guarded_Scheduler scheduler;
extern Guarded_Organizer organizer;

/* Add your code here */ 


void Application::action()
{

/* Add your code here */ 
    for (;;) {
        // prevent external interupts interupt the app execution
        {
            Secure secure;  // destroy look after we leave the {}
            cout.setpos(20, 20);
            cout << "II am app" << endl;

        }

        
        // scheduler.resume();
        organizer.kill(loop2);
    }
 
}

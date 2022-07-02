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
static char stack_loop1[4096];
static char stack_loop2[4096];
static char stack_loop3[4096];

void Application::action()
{
    Loop loop1(stack_loop1 + sizeof(stack_loop1), 1);
    Loop loop2(stack_loop2 + sizeof(stack_loop3), 2);
    Loop loop3(stack_loop3 + sizeof(stack_loop3), 3);

    organizer.ready(loop1);
    organizer.ready(loop2);


    organizer.ready(loop3);

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

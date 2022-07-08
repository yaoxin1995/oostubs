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
#include "syscall/guarded_buzzer.h"
#include "syscall/guarded_keyboard.h"
#include "machine/speaker.h"

/* Add your code here */ 
 
/* GLOBAL VARIABLES */

extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
// extern Guarded_Scheduler scheduler;
extern Guarded_Organizer organizer;
extern Guard guard;
extern Guarded_Semaphore semaphore;
extern Guarded_Keyboard guarded_keyboard;
extern Loop loop1;
extern Loop loop2;
extern Loop loop3;
/* Add your code here */ 

void Application::action()
{
    organizer.ready(loop1);
    organizer.ready(loop2);
    organizer.ready(loop3);

    for (;;) {

        Key k = guarded_keyboard.getkey();
        semaphore.p();
        cout << k << endl;
        semaphore.v();
    }   
 
}

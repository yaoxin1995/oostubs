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


 #include "user/loop.h"
 #include "thread/scheduler.h"
 #include "syscall/guarded_scheduler.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_buzzer.h"
 
extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
// extern Guarded_Scheduler scheduler;
extern Guarded_Organizer organizer; 
extern Guarded_Semaphore semaphore;
 
 
void Loop::action()
{
    Guarded_Buzzer buzzer;
    for (;;) {
       semaphore.p();
       cout <<" I am Loop: "<< i++ << endl;
       semaphore.v();

       i %= max;
       buzzer.set(5);
       buzzer.sleep();

        if (i > 200) {
	        organizer.resume();  // switch to other thread
	        i = 0;
        }

    }
 
}

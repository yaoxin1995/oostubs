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

 
extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
extern Guarded_Scheduler scheduler; 
// extern Scheduler scheduler; 
 
 
void Loop::action()
{

    for (;;) {
        // prevent external interupts interupt the app execution
        {
            Secure secure;
            cout.setpos(40, 20); 
            cout << "II am loop" << i << endl;
        }


        if (i == 1) {
            scheduler.exit();
        }
            
        scheduler.resume();
    }
 
}

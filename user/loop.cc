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

/* Add your code here */ 
 #include "user/loop.h"
 #include "thread/scheduler.h"
/* Add your code here */ 
 
extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
extern Scheduler scheduler; 
/* Add your code here */ 
 
void Loop::action()
{
/* Add your code here */

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

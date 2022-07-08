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
#include "machine/speaker.h"
#include "library/random.h"
 
extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
// extern Guarded_Scheduler scheduler;
extern Guarded_Organizer organizer; 
extern Guarded_Semaphore semaphore;
extern Speaker speaker;
Random random(3);
void Loop::action()
{
    int j = 0;
    int rn = 0;
    int k = 0;
    Guarded_Buzzer buzzer;
    for (;;) {


       
       semaphore.p();
       cout.setpos(50,10);
       cout <<" I am Loop: "<< i << endl;
       
       rn = random.number() % mod_num + 1;
       speaker.play_sound(rn);
       while(j < 100000){
            j++;
        } 
       semaphore.v();

       buzzer.set(15);
       buzzer.sleep();

        if (k > 200) {
	        organizer.resume();  // switch to other thread
	        k = 0;
        }
        j = 0;
        k++;
    }
 
}

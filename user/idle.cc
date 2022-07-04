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


#include "user/idle.h"
#include "machine/cpu.h"

extern CGA_Stream cout;
extern CPU cpu;
 
inline void Idle::action()
{

    for (;;) {
        cpu.idle();
		cout << "idle" << endl;
    }
 
}
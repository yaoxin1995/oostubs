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

#ifndef __loop_include__
#define __loop_include__

/* Add your code here */ 
 
#include "device/cgastr.h"
#include "device/keyboard.h"
#include "machine/pic.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "guard/secure.h"
#include "thread/entrant.h"
#include "syscall/thread.h"


class Loop: public Thread
{
private:
	Loop (const Loop &copy); // prevent copying
    int i;
	int mod_num;


public:
/* Add your code here */ 
	Loop (void* tos, int mod_num, int i):  Thread(tos) , i(i), mod_num(mod_num){}
	void action ();
};

#endif

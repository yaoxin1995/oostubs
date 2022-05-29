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

/* Add your code here */ 
 
/* GLOBAL VARIABLES */

extern CGA_Stream cout;
extern Plugbox plugbox;
extern PIC pic;
extern Panic panic;
extern CPU cpu;
/* Add your code here */ 
 
void Application::action()
{
/* Add your code here */ 
    for (;;) {
        // prevent external interupts interupt the app execution
        Secure secure; 
        cout.setpos(20, 20);
        cout << "endless output make me sooooooo tried";
        cout.flush();

    }
 
}

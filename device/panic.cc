/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Default interrupt handler.                                                */
/*****************************************************************************/
#include "device/panic.h"

extern CGA_Stream cout;
extern CPU cpu;
 
bool Panic::prologue() {
    cout << "Error, system stop!" << endl;
    cpu.halt();
}



 

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "machine/pit.h"

void PIT::interval(int us){
// |   bits   |   value  |  meaning
// |    0     |     0    |  Binary counting of 16 bits
// |    1-3   |    010   |  Periodic interrupt
// |    4-5   |     11   |  Low-order, then high-order counter byte
// |    6-7   |     00   |  Counter 0
// 7 6 5 4 3 2 1 0
// 0 0 1 1 0 1 0 0  = 52 = 0x34

    //set control byte
    ctrl_port.outb(0x34);
    //lower 8 Bits
 	rwport.outb(us & 0xff);
	//higher 8 Bits
	rwport.outb(  (us >>  8) );   
//
}

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* By using the PIC, hardware interrupts can be enabled or suppressed        */
/* individually. This way we can control whether interrupts of a specific    */
/* device are forwarded to the CPU at all. Even then, the interrupt handler  */
/* gets only activated if the CPU is ready to react to interrupts. This can  */
/* be controlled by using class CPU.                                         */
/*****************************************************************************/

#ifndef __pic_include__
#define __pic_include__

#include "machine/io_port.h"

// ICW : Initialization Control Word 
// OCW : Operation Control Word
//
class PIC 

{
private:
	PIC(const PIC &copy); // prevent copying
	IO_Port imr_master, imr_slave;

public:
	PIC(): imr_master(0x21), imr_slave(0xa1){};
	enum {
    timer    = 0,
    keyboard = 1
   };



//Allows the PIC to forward interrupts from the device number interrupt_device to the processor.
   void allow(int interrupt_device);

//Prevents the PIC from passing interrupts from the device number interrupt_device to the processor.
   void forbid(int interrupt_device);

//Returns the state of the masking bit of interrupt_device. If interrupts of this device 
//are not forwarded to the CPU, true shall be returned, otherwise false.
   bool is_masked(int interrupt_device);
};

#endif

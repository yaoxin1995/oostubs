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

#include "machine/pic.h"


void PIC::allow(int interrupt_device){
    int imr;

    if(interrupt_device < 8){                               // master PIC
        imr =  imr_master.inb() & ~(1 << interrupt_device); 
        imr_master.outb(imr);
    }
    else{                                                   //slave PIC
        imr =  imr_master.inb() & ~(1 << (interrupt_device - 8));
        imr_slave.outb(imr);
    }

}

void PIC::forbid(int interrupt_device){
    int imr;

    if(interrupt_device < 8){                              // master PIC
        imr =  imr_master.inb() | ~(1 << interrupt_device);
        imr_master.outb(imr);
    }
    else{                                                   //slave PIC
        imr =  imr_master.inb() | ~(1 << (interrupt_device - 8));
        imr_slave.outb(imr);
    }

}

bool PIC::is_masked(int interrupt_device){
    int imr;

    if(interrupt_device < 8){                              
        imr =  imr_master.inb();
        return ( imr & (1 << interrupt_device));

    }
    else{
        imr =  imr_master.inb();
        return ( imr & (1 << (interrupt_device -8)));

    }
}

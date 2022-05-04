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
#include "device/cgastr.h"

extern  CGA_Stream cout;
void PIC::allow(int interrupt_device){

    if(interrupt_device < 8)                         // master PIC
        imr_master.outb(imr_master.inb() & ~(1 << interrupt_device));
    else                                              //slave PIC
        imr_slave.outb(imr_slave.inb() & ~(1 << (interrupt_device - 8)));
}

//  OCW 1 的某一位置1 代表该处的 interrupt 被屏蔽
void PIC::forbid(int interrupt_device){

    if(interrupt_device < 8)                           // master PIC
        imr_master.outb(imr_master.inb() | (1 << interrupt_device));
    else                                                 //slave PIC
        imr_slave.outb(imr_slave.inb() | (1 << (interrupt_device - 8)));
}

bool PIC::is_masked(int interrupt_device){
    int imr;

    if(interrupt_device < 8){                              
        imr =  imr_master.inb();
        return ( imr & (1 << interrupt_device));

    }
    else{
        imr =  imr_slave.inb();
        return ( imr & (1 << (interrupt_device -8)));

    }
}

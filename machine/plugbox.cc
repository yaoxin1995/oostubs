/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstracts an interrupt vector table. Allows to configure handler routines */
/* for every hardware and software interrupt and every CPU exception.        */
/*****************************************************************************/

#include "machine/plugbox.h"

extern Panic panic;
Plugbox::Plugbox(){
    for(int i = 0; i < 64; i++)
        gates[i] = &panic; 
}

//assign the object, which is a special interrupt handling, 
//to the interrupt number slot in the plugbox
void Plugbox::assign (unsigned int slot, Gate& gate){
    if(slot >= 64)
        panic.trigger();

    gates[slot] = &gate;
}

//report the gate object that was entered in the plugbox for the interrupt number slot.
Gate& Plugbox:: report (unsigned int slot){
    if (slot >= 64)
        panic.trigger();

    return *gates[slot];
}
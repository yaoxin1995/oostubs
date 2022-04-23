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

Gate* gates[64];		//array of poniter to the gate object

Plugbox::Plugbox(){
    for(int i = 0; i < 64; i++){
        gates[i] = &panic;
    }
}

//assign the object, which is a special interrupt handling, 
//to the interrupt number slot in the plugbox
void Plugbox::assign (unsigned int slot, Gate& gate){
    if(slot < 64){
        gates[slot] = &gate;
    }
}
//report the gate object that was entered in the plugbox for the interrupt number slot.
Gate& report (unsigned int slot){
    return *gates[slot];
}
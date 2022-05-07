/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Using this class, we can synchronize activities with a critical section   */
/* with interrupt handlers that also access this critical section. This      */
/* synchronization takes place along the prologue/epilogue model.            */
/*****************************************************************************/

#include "guard/guard.h"
#include "machine/cpu.h"

extern CPU cpu;

void Guard::leave(){

        cpu.disable_int(); //Prologue shouldn't be interrupted
        item = (Gate *)queue.dequeue();

        while(item){      //There's still something in queue
            item->queued(false);

            cpu.enable_int();
            item->epilogue();

            cpu.disable_int();
            item = (Gate *)queue.dequeue();
        }
        retne ();
        cpu.enable_int();
    
} 

void Guard::relay(Gate* item){


    if(avail()){ // if critical section is free, item now in epilogue level
        enter();
        cpu.enable_int();
        item -> epilogue();
        leave();
    }
    // critical section is occupied, put item in queue 
    else if(!item->queued()){
        queue.enqueue(item);    //put item in queue
        item -> queued(true);
    }

    
}
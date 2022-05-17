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
    while(true){

        cpu.disable_int(); //Prologue shouldn't be interrupted
        item = (Gate *)queue.dequeue();       
       
        if(!item){           //empty queue
            break;
        }
        item->queued(false);
        cpu.enable_int();
        item->epilogue();
    }
    //INTR here is still disabled
    retne ();
    cpu.enable_int();
} 

void Guard::relay(Gate* item){

    if(item->queued()) return ;// never enqueue an item twice!!!

    //critical section free, excute epilogue
    if(avail()){ 
        enter();
        cpu.enable_int();
        item -> epilogue();
        leave();
        // cpu.disable_int();
    }
    // critical section is occupied, put item in queue 
    else {
        cpu.disable_int();
        item->queued(true);
        queue.enqueue(item);    //put item in queue
        // cpu.enable_int();
    }

    
}
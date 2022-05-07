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
        //prologue should not be allowed to interrupt during dequeue
        cpu.disable_int();
        item = (Gate *)queue.dequeue();

        if(!item){    //If the queue does not contain any elements
            cpu.enable_int();
            break;
        }
        item -> queued(false);//Item now is out of queue
        cpu.enable_int();

        item -> epilogue();       
        
        retne ();//leaves the critical section again.
    }
} 

void Guard::relay(Gate* item){
// Case: critical section is free
    if(avail()){
        enter();
        cpu.enable_int();
        item->epilogue();  //item now in epilogue level
        leave();
    }
// Case: critical section is occupied 
    else{
        if(item->queued()) return ; //item is already in queue
        else {
            item->queued(true);    
            queue.enqueue(item);    //put item in queue
            return ;
        }
    }
}
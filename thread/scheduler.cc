/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Scheduler implementation.                                                 */
/*****************************************************************************/

#include "thread/scheduler.h"
#include "thread/entrant.h"
#include "device/cgastr.h"
#include "user/idle.h"
extern CGA_Stream cout;
extern Idle idle;

void Scheduler::ready(Entrant &that) {
    ready_list.enqueue(&that);       //append a cotoutine to the ende of a ready list.
}

void Scheduler::schedule(){
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue()); 
    if(first) go(*first); 
}

void Scheduler::exit(){
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue());
    if(first)  
        dispatch(*first);
    else {
        //cout << "readly list is empty, dispath idle thread" << endl;
        dispatch(idle);
    }
} 


void Scheduler::kill(Entrant &that){
    Entrant *active_ptr = static_cast<Entrant *>(active()); 
    if(&that == active_ptr) 
        exit(); // condiserate the situation kill the thread itself.
    ready_list.remove(&that);
}

void Scheduler::resume(){
    // Set pointer to current coroutine
    Entrant *active_ptr = static_cast<Entrant *>(active()); 

    // append current coroutine into the end of the ready list if the current thread is not "idle"
    if (active_ptr != &idle) 
        ready_list.enqueue(active_ptr);
    
    // run new thread
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue());
    if (first) // if ready list is not empty, then we run the thread we got from the list, otherwise run idle
        dispatch(*first);
    else
        dispatch(idle);
}   
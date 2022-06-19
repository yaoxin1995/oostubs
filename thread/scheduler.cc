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

extern CGA_Stream cout;


void Scheduler::ready(Entrant &that) {
    ready_list.enqueue(&that);       //append a cotoutine to the ende of a ready list.
}

void Scheduler::schedule(){
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue()); 
    if(first) go(*first); 
}

void Scheduler::exit(){
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue());
    if(first)  dispatch(*first);
    // else{
    //     cout << endl << "ready list is empty now" << endl;
    //     while(!first) ;
    // }
} 


void Scheduler::kill(Entrant &that){
    Entrant *active_ptr = static_cast<Entrant *>(active()); 
    if(&that == active_ptr) exit(); // condiserate the situation kill the thread itself.
    ready_list.remove(&that);
}

void Scheduler::resume(){
    // Set pointer to current coroutine
    Entrant *active_ptr = static_cast<Entrant *>(active()); 
    // append current coroutine into the end of the ready list  
    ready_list.enqueue(active_ptr);

    active_ptr = static_cast<Entrant *>(ready_list.dequeue());
    if(active_ptr) dispatch(*active_ptr);
}   
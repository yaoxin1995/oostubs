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
    ready_list.enqueue(&that);
}

void Scheduler::schedule(){
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue());
    if(first) go(*first);
}

void Scheduler::exit(){
    Entrant *first = static_cast<Entrant *>(ready_list.dequeue());
    if(first)  dispatch(*first);
    else{
        cout << endl << "ready list is empty now" << endl;
        while(!first) ;
    }
} 


void Scheduler::kill(Entrant &that){
    ready_list.remove(&that);
}

void Scheduler::resume(){
    // Set pointer to current thread
    Entrant *active_ptr = static_cast<Entrant *>(active()); 
    // append current thread into ready list  
    ready_list.enqueue(active_ptr);

    active_ptr = static_cast<Entrant *>(ready_list.dequeue());
    if(active_ptr) dispatch(*active_ptr);
}   
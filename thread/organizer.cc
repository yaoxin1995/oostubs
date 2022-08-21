/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Organizer is a special scheduler that additionally allows processes   */
/* (Customer objects) to wait for events (Waitingroom objects).              */
/*****************************************************************************/

/* Add your code here */ 
#include "organizer.h"
#include "customer.h"
#include "meeting/waitingroom.h"

void Organizer::block (Customer& customer, Waitingroom& waitingroom) {
    waitingroom.enqueue(&customer);
    customer.waiting_in(&waitingroom);
    if(&customer == active())
        exit();   
    else
        kill(customer);// use exit() can only exit currently activ customer, 
                        //but use kill() can also kill this customer itself.

}

void Organizer::wakeup (Customer& customer) {
    customer.waiting_in(0);
    ready(customer);
}

void Organizer::kill (Customer& that) {
    Waitingroom* room = that.waiting_in();

    if (room) // when thread is in a waitingroom, in this case we remove if from ready list
        room->remove(&that);
    else // if thread is in ready list, then kill it
        Scheduler::kill(that);
    
}
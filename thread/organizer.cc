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
        kill(customer);// use exit() can only exit currently activ customer, but use kill() can also kill this customer itself.

}

void Organizer::wakeup (Customer& customer) {
    customer.waiting_in(0);
    ready(customer);
}

void Organizer::kill (Customer& that) {
    Waitingroom* room = that.waiting_in();
    if (room) {
    room->remove(&that);
    } else {
    Scheduler::kill(that);
    }
}
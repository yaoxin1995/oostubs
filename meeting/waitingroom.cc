/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements a list of processes (Customer objects) that are all waiting    */
/* for a specific event.                                                     */
/*****************************************************************************/

#include "waitingroom.h"
#include "object/chain.h"
#include "thread/customer.h"
#include "syscall/guarded_organizer.h"
#include "device/cgastr.h"

extern CGA_Stream cout;
extern Guarded_Organizer organizer;

Waitingroom::~Waitingroom () {
    Customer* customer;
    while(Chain *chain = dequeue()){             //removes and wakeups the 1.waitting process until the list is empty
        cout << "wake up threads in Waitingroom destructor" << endl;
        customer = static_cast<Customer*>(chain);
        organizer.Organizer::wakeup(*customer);
    }
}

void Waitingroom::remove(Customer* customer){
    Queue::remove(customer);
    // Q: why not organizer.wakeup?  
    // ==> prevent double enter the secure section by call the wakeup methed in base class (Organizer)
    organizer.Organizer::wakeup(*customer);
}
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The class Semaphore implements the synchronization concept of the         */
/* counting semaphore.                                                       */
/*****************************************************************************/

#include "meeting/semaphore.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer organizer;

void Semaphore::p(){
    if(counter > 0){
        counter = counter - 1;
    }else{
        organizer.Organizer::block(*static_cast<Customer *>(organizer.active()),*this);
    }
}

void Semaphore::v(){
    if(Chain *chain = dequeue())
        organizer.Organizer::wakeup(*static_cast<Customer *>(chain));  //at least one customer on the waiting list, wake up the first
    else 
        counter = counter + 1;
}

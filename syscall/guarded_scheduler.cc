/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ S C H E D U L E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements the system-call interface to the Scheduler.                    */
/*****************************************************************************/

/* Add your code here */ 
#include "syscall/guarded_scheduler.h"
#include "guard/secure.h"

/**
 * @brief This method registers the process that with the scheduler.
 * 
 * @param that 
 */
void Guarded_Scheduler::ready (Thread& that) {
    Secure secure;
    this->Scheduler::ready (that);
}

/**
 * @brief With this method, a process can terminate itself.
 * 
 */
void Guarded_Scheduler::exit () {
    Secure secure;
    this->Scheduler::exit();
}


/**
 * @brief With this method, a process can kill another (that).
 * 
 * @param that 
 */
void Guarded_Scheduler::kill (Thread& that) {
    Secure secure;
    this->Scheduler::kill(that);
}

/**
 * @brief This method can be used to trigger a process switch
 * 
 */
void Guarded_Scheduler::resume () {
    Secure secure;
    this->Scheduler::resume();
}
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Handles timer interrupts by managing a time slice and triggering a        */
/* process switch if necessary.                                              */
/*****************************************************************************/

/* Add your code here */ 
#include "device/watch.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

extern Bellringer bellringer;
extern Plugbox plugbox;
extern PIC pic;
extern Guarded_Organizer organizer;

/* Add your code here */ 
 void Watch::windup (){
     // register with the Plugbox plugbox 
     plugbox.assign(Plugbox::timer, *this);
     // allow the interrupts
     pic.allow(PIC::timer);
 }

 //Interrupt handler, guardian first call prologue(), if prologue return ture then request timer's epilogue  
 bool Watch::prologue (){
     return true;
 }


 void Watch::epilogue (){
     bellringer.check();
     organizer.Scheduler::resume(); //Q:why not use resume in guarded_scheduler, prevent double enter in critical section
 }


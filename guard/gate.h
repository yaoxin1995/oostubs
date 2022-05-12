/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Class of objects that handle interrupts.                                  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

class Gate : public Chain{
    bool is_attached_to_eplog_queue;
public:
    
    Gate():is_attached_to_eplog_queue(false){}

    // prevent memory leak
    virtual ~Gate(){}

    virtual bool prologue () = 0;

    virtual void epilogue () {}

    // Stores whether the given object is currently in an epilog queue.
    void queued (bool q) 
    {
        is_attached_to_eplog_queue = q;
    }

    // Method for querying whether the given object is currently in an epilog queue.
    bool queued () 
    {
        return is_attached_to_eplog_queue;
    }



};

#endif

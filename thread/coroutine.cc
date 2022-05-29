/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Represents the abstraction of a coroutine.                                */
/* In the constructor, we set up the initial context of the coroutine. go()  */
/* activates the first coroutine. All further coroutine switches should be   */
/* initiated by resume().                                                    */
/* To be able to save the context at a couroutine switch, every Coroutine    */
/* object contains a struct toc that stores the values of all non-volatile   */
/* registers.                                                                */
/*****************************************************************************/

#include "thread/coroutine.h"

// Functions that are implemented at C or assembler level must be declared as
// extern "C", because they do not conform to C++ name mangling.
extern "C" {
/* Add your code here */ 
    void toc_settle (struct toc* regs, void* tos, void (*kickoff)(void*, void*, void*, void*, void*, void*, void*), void* object);

    void toc_go (struct toc* regs);

    void toc_switch (struct toc* regs_now, struct toc* regs_then);

    void kickoff (void *dummy1, void *dummy2, void *dummy3, void *dummy4, void *dummy5, void *dummy6, void *object);
}
/* Add your code here */ 


Coroutine::Coroutine (void* tos) 
{
    toc_settle(&regs, tos, kickoff, this);
}

void Coroutine::go()
{
    toc_go(&regs);
} 

void Coroutine::resume (Coroutine& next)
{
    toc_switch(&regs, &next.regs);
} 


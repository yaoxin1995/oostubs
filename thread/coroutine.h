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

#ifndef __Coroutine_include__
#define __Coroutine_include__

#include "machine/toc.h"



class Coroutine {
private:
	Coroutine(const Coroutine &copy); // prevent copying
/* Add your code here */ 

public:

	struct toc regs;

	/**
	 * @brief Construct a new Coroutine object
	 * In the coroutine constructor, the register values are initialized so that the 
	 * stack pointer initially points to tos and on first activation execution begins with the kickoff function.
	 * @param tos 
	 */
	Coroutine (void* tos);

	/**
	 * @brief 
	 * This method is used for the first activation of the first coroutine in the system. 
	 * Therefore no register values must be saved here.
	 */
	void go ();
	/**
	 * @brief 
	 * This method triggers a coroutine switch. The current contents of the non-volatile registers are saved 
	 * in the toc element and replaced by the values of next (the toc element of the next coroutine).
	 * @param next 
	 */
	void resume (Coroutine& next);

	/**
	 * @brief 
	 * The method action represents the actual job of the coroutine. 
	 * However, since not all coroutines in the system should do the same, 
	 * action can only be defined in a specialized class (e.g. in Application).
	 */
	virtual void action () = 0;
};

#endif

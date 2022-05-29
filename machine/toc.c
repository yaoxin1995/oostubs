/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 T O C                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The toc struct is used to save the values of the non-volatile registers   */
/* in case of a context switch. toc_settle prepares the initial stack and    */
/* the toc struct for the first activation.                                  */
/*****************************************************************************/
#include <stdint.h>
#include "machine/toc.h"

/*

		       +-------------------+  \
		       | arg 7             |  >- kichof's stack frame
		       +-------------------+  |    
		       | ret %eip(0)       |  /
		       +===================+   
		       | ret %eip(kickoff) |   \
		%esp-> +-------------------+   >- resume's stack frame
		       |           		   |   |
               +-------------------+   /
*/


// TOC_SETTLE: Prepares a coroutine context for its first activation.
void toc_settle(struct toc *regs, void *tos,
		void (*kickoff)(void *, void *, void *, void *, void *, void *, void *),
		void *object)
{
/* Add your code here */
	void **stack_pointer_array = (void **)tos;

	// create stack frame for kickoff

	*(--stack_pointer_array) = object;   // 7th parameter

	*(--stack_pointer_array) = 0; // kichof 的 caller's return adress (non-existent), 因为kickof 是第一个 程序， 所以其没有对应的 caller

	*(--stack_pointer_array) = kickoff;

	//TODO: handle rbp
	regs->rsp = stack_pointer_array;

}

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "device/cgastr.h"
#include "device/keyboard.h"
#include "machine/pic.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "guard/secure.h"
#include "thread/coroutine.h"

class Application: public Coroutine
{
private:
	Application (const Application &copy); // prevent copying

public:
/* Add your code here */ 
	Application (void* tos): Coroutine(tos) {}
	void action ();
};

#endif

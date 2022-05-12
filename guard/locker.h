/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Locker class implements a lock that can be used to protect critical   */
/* sections. However, the variable only indicates whether the critical       */
/* section is free. Potentially necessary waiting, and protection for        */
/* counting functionality, must be implemented elsewhere.                    */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "device/cgastr.h"
#include "device/panic.h"

extern CGA_Stream cout;
extern Panic panic;

class Locker {
private:
	bool is_locked;
	Locker(const Locker &copy); // prevent copying
/* Add your code here */ 

public:
	// Initializes the lock variable to mark the critical section as free
	Locker() : is_locked(false) {}

	// This method must be called when entering the critical section.
	void enter () 
	{
		if (is_locked) {
			cout << "Error already in critical section" << endl;
			panic.prologue();
		}

		is_locked = true;
	}

	// This method leaves the critical section again.
	void retne () 
	{
		if (!is_locked) {
			cout << "Error not in critical section" << endl;
			panic.prologue();
		}

		is_locked = false;
	}
	// This method indicates whether the critical section is free.
	bool avail () {
		return !is_locked;
	}



};

#endif

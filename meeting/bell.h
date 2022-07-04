/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Bell is an abstract base class that allows the time-controlled triggering */
/* of an activity. For this purpose, it has an internal counter that is      */
/* managed by the Bellringer.                                                */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

/* Add your code here */ 
#include "object/chain.h"
class Bell
/* Add your code here */ 
: public Chain
{
private:
	Bell(const Bell &copy); // prevent copying
	int counter; 

public:
	Bell():counter(0) {}
/* Add your code here */

	// Set or get the counter.
	void wait (int value) {
		counter = value;
	}

	int wait () {
		return counter;
	}

	void tick () {
		--counter;
	}

	// Returns true, when the time has expired
	bool run_down() {
		if (counter <= 0)
			return true;
		return false;

	}

	// Called by the bell ringer when it is the right time.
	virtual void ring () = 0;
};

#endif

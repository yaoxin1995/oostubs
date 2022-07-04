/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* An "alarm clock" is a synchronization object that allows one or more      */
/* threads to put themselves to sleep for a specified time.                  */
/*****************************************************************************/

#ifndef __Buzzer_include__
#define __Buzzer_include__

/* Add your code here */ 
#include "meeting/waitingroom.h"
#include "meeting/bell.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer organizer;
extern Bellringer bellringer;

// An "alarm clock" is a synchronization object that allows
// one or more threads to put themselves to sleep for a specified time.
class Buzzer
/* Add your code here */
: public Bell, public Waitingroom
{
private:
	Buzzer(const Buzzer &copy); // prevent copying
/* Add your code here */ 
public:
	// In the constructor, the alarm clock is initially switched off
	Buzzer () {}

	void destroy() {
		bellringer.cancel(this);
		Customer* customer = 0;
		while(customer = static_cast<Customer *>(dequeue()))
			organizer.Organizer::wakeup(*customer);
			
	}

	// In the destructor, the Bellringer is informed that he no longer needs to ring. 
	// Furthermore, all waiting threads are woken up.
	virtual ~Buzzer() {
		destroy();
	}

	//Called by the Bellringer when the waiting time has expired. 
	//Wakes up sleeping threads if necessary.
	virtual void ring() {

		Customer* customer = nullptr;

		while (customer = static_cast<Customer*> (dequeue()))
		{
			remove(customer);
		}
		
	}

	// Setting the alarm clock
	void set (int ms) {
		bellringer.cancel(this);
		bellringer.job(this, ms);
	}

	// Let caller thread sleep until the alarm clock ring
	void sleep () {
		if (wait() > 0) {
    		Customer *customer = static_cast<Customer *>(organizer.active());
    		enqueue(customer);
    		organizer.Organizer::block(*customer, *this);
  		}
	}

};

#endif

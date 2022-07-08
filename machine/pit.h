/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__
#include "machine/io_port.h"

// |Port (1.PIT)	|Register		|Access modes
// |0x40	    	|Counter 0		|write/read
// |0x43			|Ctrl register  |write only

class PIT {
private:
	PIT(const PIT &copy); // prevent copying
	int interv;
	IO_Port ctrl_port;
	IO_Port rwport;
public:
	PIT(int us) : ctrl_port(0x43), rwport(0x40){
		interval (us);
	}
	/* Indicates which interrupt interval was set. */
	int interval() {
		return interv;
	}
	/* Sets a new interrupt interval. */
	void interval(int us);

};

#endif

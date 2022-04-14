/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The O_Stream class defines the << operator for several pre-defined data   */
/* types and thereby realizes output functionality similar to C++'s iostream */
/* library. By default, this class supports printing characters, strings and */
/* integer numbers of various bit sizes. Another << operator allows to use   */
/* so-called 'manipulators'.                                                 */
/*                                                                           */
/* Besides class O_Stream this file also defines the manipulators hex, dec,  */
/* oct and bin for choosing the basis in number representations, and endl    */
/* for implementing an (implicitly flushing) line termination.               */
/*****************************************************************************/

#ifndef __o_stream_include__
#define __o_stream_include__

#include "object/strbuf.h"

class O_Stream : public Stringbuffer
{
private:
	O_Stream(const O_Stream &copy); // prevent copying
/* Add your code here */
	/*
	can initialize integer types in the .h; 
	all other types have to be initialized outside the class 
	declaration, and only once.
	*/
	const static char numbers[];
	int unsigned_long_to_chararray(unsigned long number, char *char_array, int array_length);

public:

	enum BASE {
		DEC = 10, // 10
		HEX = 16, // 16
		OCT = 8, // 8
		BIN = 2 // 2
	};

	O_Stream(BASE base = DEC);

	/* Appending the character c to the collected characters*/
	O_Stream& operator<< (unsigned char c);
	O_Stream& operator<< (char c);

	/*Append the number number in the selected number system*/
	O_Stream& operator<< (unsigned short number);
	O_Stream& operator<< (short number);
	O_Stream& operator<< (unsigned int number);
	O_Stream& operator<< (int number);
	O_Stream& operator<< (unsigned long number);
	O_Stream& operator<< (long number);

	/*Appending the pointer value pointer in hexadecimal system*/
	O_Stream& operator<< (void *pointer);

	/*Append the null-terminated string text (without the null-termination)*/
	O_Stream& operator<< (char *text);

	/*Call of the manipulator function fkt*/
	O_Stream& operator<< (O_Stream& (*fkt) (O_Stream&));

	/*
	 * A friend function is a function that is specified outside a class but has 
	 * the ability to access the class members’ protected and private data. A friend can 
	 * be a member’s function, function template, or function, or a class or class template, 
	 * in which case the entire class and all of its members are friends.
	 */

	friend O_Stream& endl (O_Stream& os);

	friend O_Stream& bin (O_Stream& os);

	friend O_Stream& oct (O_Stream& os);

	friend O_Stream& dec (O_Stream& os);

	friend O_Stream& hex (O_Stream& os);

 protected:
	BASE base;
};

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          M A N I P U L A T O R S                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The functions below all receive and return a reference to an O_Stream     */
/* object. Because class O_Stream defines an operator<< for functions with   */
/* this signature, they can be called in this operator's implementation and  */
/* even be embedded in a "stream" of outputs. A manipulator's task is to     */
/* influence subsequent output, e.g. by switching to a different number      */
/* system.                                                                   */
/*---------------------------------------------------------------------------*/

// ENDL: inserts a newline in the output and flushes the buffer
O_Stream& endl (O_Stream& os);

// BIN: selects the binary number system
O_Stream& bin (O_Stream& os);

// OCT: selects the octal number system
O_Stream& oct (O_Stream& os);

// DEC: selects the decimal number system
O_Stream& dec (O_Stream& os);

// HEX: selects the hexadecimal number system
O_Stream& hex (O_Stream& os);
#endif

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       S T R I N G B U F F E R                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Stringbuffer class provides a buffer for collecting characters to be  */
/* printed to an output device, in our case the PC screen. The actual output */
/* occurs once the buffer is full, or when the user explicitly calls         */
/* flush().                                                                  */
/* As Stringbuffer is intended to be device independent, flush() is a        */
/* (pure) virtual method that must be defined by derived classes.            */
/*****************************************************************************/

#ifndef __strbuf_include__
#define __strbuf_include__

#define DEFAULT_BUF_SIZE 100
class Stringbuffer {
private:
	char buffer[DEFAULT_BUF_SIZE];
	int buf_size;
	int current_buf_size;


	Stringbuffer(const Stringbuffer &copy); // prevent copying

/* Add your code here */ 
public:

	Stringbuffer() {
		buf_size = 0;
		current_buf_size = 0;
	}

	int get_buffer_size () {
		return current_buf_size;
	}

	void put (char c) {

		buffer[current_buf_size++] = c;

		if (current_buf_size == buf_size)
			flush();
	}

	virtual void flush()=0;

};

#endif

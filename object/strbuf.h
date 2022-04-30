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

	int current_buf_size;


	Stringbuffer(const Stringbuffer &copy); // prevent copying

protected:
	char buffer[DEFAULT_BUF_SIZE];
/* Add your code here */ 
protected:
  	enum {
    	BUFFER_SIZE = 1024
  	};
  	char buffer[BUFFER_SIZE];

  	int size;



public:
  Stringbuffer() : size(0) {}

  void put(char c);

  virtual void flush() = 0;
};

#endif
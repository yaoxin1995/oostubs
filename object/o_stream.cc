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

#include "object/o_stream.h"

/* Add your code here */ 
#define CHAR_ARRAY_LEN 20

O_Stream::O_Stream (BASE base) 
{
    this->base = base;
}


int O_Stream::unsigned_long_to_chararray(unsigned long number, char *char_array, int array_length) {
    
    static char numbers[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; 
    int i = array_length - 1;
    char remainder;
    BASE base = this->base;

/* Format
    Binary format：0bXXXX
    OCT: 0XXXX
    HEX: 0xXXXX
*/
    do {
        remainder = number % base;
        number /= base;
        char_array[i--] = numbers[remainder];
    } while (number);

    if (base == HEX)
        char_array[i--] = 'x';
    
    if (base == BIN)
        char_array[i--] = 'b';
    
    char_array[i] = 0;

    return i;
}


O_Stream& O_Stream::operator<< (long number) 
{
    bool has_minus = false;
    char char_array[CHAR_ARRAY_LEN];  // ???
    int i = CHAR_ARRAY_LEN;

    if (number < 0) {
        has_minus = true;
        number = -number;
    }

    i = unsigned_long_to_chararray((unsigned long)number, char_array, CHAR_ARRAY_LEN);

    if (has_minus)
        char_array[--i] = '-';

    while (i < CHAR_ARRAY_LEN)
        this->put(char_array[i++]);

}

O_Stream& O_Stream::operator<< (unsigned long number)
{
    char char_array[CHAR_ARRAY_LEN];  // ???
    int i = CHAR_ARRAY_LEN;


    i = unsigned_long_to_chararray(number, char_array, CHAR_ARRAY_LEN);

    while (i < CHAR_ARRAY_LEN)
        this->put(char_array[i++]);

}

O_Stream& O_Stream::operator<< (unsigned char c)
{
    return operator<<((unsigned long)c);
}

O_Stream& O_Stream::operator<< (char c)
{
    return operator<<((long)c);
}

O_Stream& O_Stream::operator<< (unsigned short number) 
{
    return operator<<((unsigned long)number);
}

O_Stream& O_Stream::operator<< (short number)
{
    return operator<<((long)number);
}

O_Stream& O_Stream::operator<< (unsigned int number)
{
    return operator<<((unsigned long)number);
}

O_Stream& O_Stream::operator<< (int number)
{
    return operator<<((long)number);
}


/**
 * @brief 
 * print the pointer value, i.e, get the memory address (location) that the pointer points to.
 * for example, int *a = b; this func should print the address of variable b
 * @param pointer 
 * @return O_Stream& 
 */
O_Stream& O_Stream::operator<< (void *pointer) 
{
    BASE tmp = this->base;

    this->base = HEX;

    operator<<((unsigned long)(pointer));

    return *this;


}

O_Stream& O_Stream::operator<< (char* text)
{
    int i = 0;

    while (*text != '0')
        operator<<(*text);
    
    return *this;
}

/**
 * @brief 

 * @param fkt 
 * @return O_Stream& 
 */
O_Stream& O_Stream::operator<< (O_Stream& (*fkt) (O_Stream&))
{   
    /*
    * this is a pointer, and *this is a dereferenced pointer.
    * If you had a function that returned this, it would be a pointer to the 
    * current object, while a function that returned *this would be a "clone" of 
    * the current object, allocated on the stack -- unless you have specified the return 
    * type of the method to return a reference.
    */
    return (*fkt)(*this);
}


O_Stream& endl (O_Stream& os) 
{
    os.put('\n');
    return os;
}

O_Stream& bin (O_Stream& os)
{
    os.base = O_Stream::BIN;
    return os;
}

O_Stream& oct (O_Stream& os)
{
    os.base = O_Stream::OCT;
    return os;
}

O_Stream& dec (O_Stream& os)
{
    os.base = O_Stream::OCT;
    return os;
}

O_Stream& hex (O_Stream& os)
{
    os.base = O_Stream::HEX;
    return os;
}



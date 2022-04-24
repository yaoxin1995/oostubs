/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C G A _ S T R E A M                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The CGA_Stream class allows to print different data types as text strings */
/* to a PC's CGA screen.                                                     */
/* For attributes/colors and cursor positioning use the methods of class     */
/* CGA_Screen.                                                               */
/*****************************************************************************/

#include "device/cgastr.h"

void CGA_Stream::flush (){

    int current_buf_size = get_buffer_size();

    print(buffer, current_buf_size, DEFAULT_ATTRIBUTES_WITHOUT_BLINK);

    reset_buffer_size();
}

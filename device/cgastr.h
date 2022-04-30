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

#ifndef __cgastr_include__
#define __cgastr_include__

#include "object/o_stream.h"
#include "machine/cgascr.h"

class CGA_Stream: public O_Stream, public CGA_Screen
/* Add your code here */ 
{
private:
      CGA_Stream(CGA_Stream &copy); // prevent copying
/* Add your code here */ 
public:
  CGA_Stream() {}
  ~CGA_Stream() { flush(); }

  // Mit dieser Methode wird der Inhalt des Zeichenpuffers auf dem
  // CGA-Bildschirm ausgegeben.
  void flush();
};

#endif

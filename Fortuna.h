#ifndef FORTUNA_H
#define	FORTUNA_H

#include <inttypes.h>

//#include <Arduino.h>
//#include <WProgram.h>
#include "Accumulator.h"
#include<iostream>


class Fortuna
{
  public :
    Fortuna();
    void FortunaSerialPrint();
  private:
    Accumulator accumulator;
  

  
};
#endif	/* FORTUNA_H */


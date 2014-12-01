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
    bool RegisterSource(Source *source);
    void GatherEntropy(){accumulator.AddEventData();}
    uint8_t* GetRandomData(uint8_t byteSize)
    {
        return accumulator.RandomData(byteSize);
    }
  private:
    Accumulator accumulator;
  

  
};
#endif	/* FORTUNA_H */


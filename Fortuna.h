#ifndef FORTUNA_H
#define	FORTUNA_H

#include "Accumulator.h"
#include <inttypes.h>

class Fortuna
{
  public :
    Fortuna();
    bool RegisterSource(Source *source);
    void GatherEntropy(){accumulator.AddEventData();}
    uint8_t* GetRandomData(uint32_t byteSize)
    {
        return accumulator.RandomData(byteSize);
    }
  private:
    Accumulator accumulator;
  

  
};
#endif	/* FORTUNA_H */


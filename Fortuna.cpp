#include "Fortuna.h"

Fortuna::Fortuna()
:accumulator(Accumulator())
{
  
}

bool Fortuna::RegisterSource(Source *source)
{
    accumulator.registerEntropySource(source);
}



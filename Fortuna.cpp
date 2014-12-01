#include "Fortuna.h"

Fortuna::Fortuna()
:accumulator(Accumulator())
{
  
}


void Fortuna::FortunaSerialPrint()
{
   //Serial.println("Banter"); 
    std::cout<<"Banter";
}

bool Fortuna::RegisterSource(Source *source)
{
    accumulator.registerEntropySource(source);
}



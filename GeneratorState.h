#ifndef GENERATOR_STATE_H
#define	GENERATOR_STATE_H

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100 
 #include <Arduino.h>
#endif

#define MAX_COUNTER_SIZE 16 //This will be 2^128 as 8*16 = 128

class GeneratorState
{
  public:
    GeneratorState();
    ~GeneratorState(){delete[] key; delete[] counter;}
    uint8_t getKeySize(){return keySize;}
    uint8_t* getKey(){return key;}
    uint8_t* getCount(){return counter;}
    void setKey(uint8_t *newKey, uint8_t newKeySize);
    bool isZeroCount();
    void addToCounter();
    
  private:
    uint8_t* key;
    uint16_t keySize;
    uint8_t* counter;
};

#endif

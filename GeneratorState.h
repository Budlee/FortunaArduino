#ifndef GENERATOR_STATE_H
#define	GENERATOR_STATE_H
//#include <Arduino.h>
//#include <WProgram.h>
#include <inttypes.h>

class GeneratorState
{
  public:
    GeneratorState(){keySize=0;key = new uint8_t[0];counter = 0;}
    uint8_t getKeySize(){return keySize;}
    uint8_t* getKey(){return key;}
    uint16_t getReseedCount(){return counter;}
    void setKeySize(uint8_t newKeySize){keySize = newKeySize;}
    void setKey(uint8_t *newKey){delete(key);key = newKey;}
    void addToCounter(){++counter;}
    
  private:
    uint8_t* key;
    uint8_t keySize;
    uint16_t counter;
};

#endif

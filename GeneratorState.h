#ifndef GENERATOR_STATE_H
#define	GENERATOR_STATE_H
#if defined(ARDUINO) && ARDUINO >= 100 
 #include <Arduino.h>
//#include <WProgram.h>
#endif
#include <inttypes.h>

class GeneratorState
{
  public:
    GeneratorState(){keySize=0;key = new uint8_t[0];counter = 0x0;}
    ~GeneratorState(){delete[] key;}
    uint8_t getKeySize(){return keySize;}
    uint8_t* getKey(){return key;}
    uint16_t getCount(){return counter;}
    void setKey(uint8_t *newKey, uint8_t newKeySize)
    {
        keySize = newKeySize;
        delete[] key;
        key = new uint8_t[newKeySize];
        #if defined(ARDUINO) && ARDUINO >= 100 
            memcpy_P(newKey , newKey, newKeySize);
        #else
            std::copy(newKey, newKey+newKeySize, key);
        #endif
    }
    void addToCounter(){++counter;}
    
  private:
    uint8_t* key;
    uint16_t keySize;
    uint16_t counter;
};

#endif

#ifndef GENERATOR_H
#define	GENERATOR_H

#include "GeneratorState.h"
#include "sha256.h"
#include "AES.h"
#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100 
#include <Arduino.h>
#else
#include <math.h>
#include <algorithm> 
#endif


//#include <WProgram.h>

//#define MAX_BLOCK_GENERATE_SIZE 8 //This can be adjusted but if it is more could cause memmory issues

class Generator {
public:
    Generator();
    ~Generator();
    void reseedGenerator(uint8_t* seed, uint16_t seedSize);
    uint8_t* generateRandomData(uint32_t numberOfBytes,uint8_t *randomBytes);
    uint8_t* getCount() { return generatorState.getCount();}

//    bool isAvaliable() {
//        return generatorState.getReseedCount();
//    }
private:
    bool generateBlocks(uint8_t numberOfBlocks, uint8_t* pseudroRandomData);
    GeneratorState generatorState;
    AES aes;
    Sha256Class sha;
    uint8_t *cipherText;
    uint8_t *aesPlainText; // reuse the values;

};

#endif

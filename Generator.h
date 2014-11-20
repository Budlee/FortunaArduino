#ifndef GENERATOR_H
#define	GENERATOR_H

#include <inttypes.h>

//#include <Arduino.h>
//#include <WProgram.h>
#include "GeneratorState.h"
#include "sha256.h"
//#include <utility/sha256.h>
//#include <utility/AES.h>

//#define MAX_BLOCK_GENERATE_SIZE 8 //This can be adjusted but if it is more could cause memmory issues

class Generator {
public:
    Generator();
    void reseedGenerator(uint8_t* seed, uint8_t seedSize);
    uint8_t* generateRandomData(uint8_t numberOfBytes);

    bool isAvaliable() {
        return generatorState.getReseedCount();
    }
private:
    //AES aes;
    bool generateBlocks(uint8_t numberOfBlocks, uint8_t* pseudroRandomData);
    GeneratorState generatorState;

    uint8_t plainText[16];
    uint8_t cipherText[16];
};

#endif

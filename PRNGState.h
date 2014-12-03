#ifndef PRNGSTATE_H
#define	PRNGSTATE_H

#include <inttypes.h>

#include "Generator.h"
#include "Pool.h"

#define POOL_SIZE 32

class PRNGState {
public:
    PRNGState();
    ~PRNGState();
    Pool* getPool(uint8_t poolNumber);
    void reseed(uint8_t *entropy, uint16_t entropySize) { generator.reseedGenerator(entropy, entropySize);addToReseedCount();}
    uint16_t getReseedCount() { return reseedCount;}
    void addToReseedCount() { ++reseedCount;}
    uint8_t* generateRandomData(uint16_t numberOfBytes,uint8_t *randomBytes){return generator.generateRandomData(numberOfBytes, randomBytes);}
    uint8_t getPoolSize(){return POOL_SIZE;}
private:
    Pool *pools;
    uint16_t reseedCount;
    Generator generator;
};

#endif	/* PRNGSTATE_H */


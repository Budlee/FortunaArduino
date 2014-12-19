/* 
 * File:   Pool.h
 * Author: matt
 *
 * Created on 24 November 2014, 20:27
 */

#ifndef POOL_H
#define	POOL_H

#include <inttypes.h>

#define MAX_INPUT_ENTROPY_POOL_SIZE_BYTES 32
#define MAX_INPUT_ENTROPY_POOL_SIZE_BITS 256 //32bytes = 32 * 8 = 256

#define MAX_ENTROPY_POOL_SIZE_BYTES 64
#define MAX_ENTROPY_POOL_SIZE_BITS 512 //64bytes = 64 * 8 = 512

#define ENTROPY_BLOCKS MAX_ENTROPY_POOL_SIZE_BYTES

class Pool
{
public:
    Pool();
    ~Pool();
    uint8_t length(){return entropyLength/8;}
    void addEntropy(uint8_t *newEntropy, uint8_t entropySize, uint8_t sourceNumber);
    uint8_t* getEntropy(){return entropyCache;}
    void clear();
private:
    uint16_t entropyLength;
    uint8_t *entropyCache;
};

#endif	/* POOL_H */


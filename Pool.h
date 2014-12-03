/* 
 * File:   Pool.h
 * Author: matt
 *
 * Created on 24 November 2014, 20:27
 */

#ifndef POOL_H
#define	POOL_H

#include <inttypes.h>

#define MAX_ENTROPY_POOL_SIZE 32

class Pool
{
public:
    Pool();
    uint8_t length(){return entropyLength;}
    void addEntropy(uint32_t newEntropy, uint8_t entropySize);
    uint32_t getEntropy(){return entropyCache;}
    void clear(){entropyLength=0x0; entropyCache = 0x0;}
private:
    uint8_t entropyLength;
    uint32_t entropyCache;
};

#endif	/* POOL_H */


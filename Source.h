#ifndef SOURCE_H
#define	SOURCE_H

#include<inttypes.h>

class Source {
public:
    virtual uint8_t* getEntropy(uint8_t *retPoolNumber, uint8_t* retEntropySize) =0;
    virtual uint8_t getSourceNumber(void) =0;
};

#endif	/* POOL_H */


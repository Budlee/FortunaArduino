#ifndef SOURCE_H
#define	SOURCE_H

#include<inttypes.h>

class Source {
public:
    virtual uint8_t* getEntropy(uint8_t *retPoolNumber, uint8_t* retEntropySize) =0;
    uint8_t getSourceNumber(){return sourceId;}
    void setSourceId(uint8_t newSourceId){sourceId = newSourceId;}
private:
    uint8_t sourceId;
};

#endif	/* POOL_H */


/* 
 * File:   MyPool.h
 * Author: matt
 *
 * Created on 24 November 2014, 08:45
 */

#ifndef MYSOURCE_H
#define	MYSOURCE_H

#include <inttypes.h>
#include "Source.h"


class MySource: public Source {
public:
    MySource();
    ~MySource();
    uint8_t* getEntropy(uint8_t *retPoolNumber, uint8_t* retEntropySize);
    void setReturnValue(uint8_t *v){returnValue = v;}
private:
    uint8_t poolNumber;
    uint8_t *returnValue;
};

#endif	/* MYPOOL_H */


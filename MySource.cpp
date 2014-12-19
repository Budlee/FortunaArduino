/* 
 * File:   MyPool.cpp
 * Author: matt
 * 
 * Created on 24 November 2014, 08:45
 */

#include "MySource.h"

MySource::MySource()
:poolNumber(0x0)
,returnValue(new uint8_t[2])
{
    
}

MySource::~MySource()
{
    delete[] returnValue;
}

uint8_t* MySource::getEntropy(uint8_t* retPoolNumber, uint8_t* retEntropySize)
{
    
    *retPoolNumber = poolNumber;
    if(poolNumber >= 31)
    {
        poolNumber = 0;
    }
    else
    {
        ++poolNumber;
    }
    
    *retEntropySize = 16;
    delete[] returnValue;
    returnValue = new uint8_t[4];
    returnValue[0] = 0x21;
    returnValue[1] = 0x43;
    returnValue[2] = 0x65;
    returnValue[3] = 0x87;
    uint8_t *ptrReturnValue = returnValue;
    
    return ptrReturnValue;
    
}
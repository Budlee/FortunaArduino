/* 
 * File:   MyPool.cpp
 * Author: matt
 * 
 * Created on 24 November 2014, 08:45
 */

#include "MySource.h"

MySource::MySource()
:poolNumber(0x0)
,returnValue(0x01)
{
    
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
    
    *retEntropySize = 8;    
    uint8_t returnValue = 0x01;
    uint8_t *ptrReturnValue = &returnValue;
    
    return ptrReturnValue;
    
}
#include "Pool.h"

Pool::Pool()
: entropyCache(new uint8_t[ENTROPY_BLOCKS])
, entropyLength(0x0)
{

}

Pool::~Pool()
{
    delete[] entropyCache;
}

void Pool::addEntropy(uint8_t *newEntropy, uint8_t newEntropySize, uint8_t sourceNumber)
{
    //As the maximum entropy size can be 255 I do not need to checkthe input size is less that 32bytes= 32*8 = 256
    if(newEntropySize < 0)
    {
        return;
    }
    
    uint8_t entropySize = newEntropySize + 16;
    uint8_t bytesToShift = entropySize/8;
    uint8_t bitsToShift = entropySize%8;
    
    for(uint8_t entropyIndex = ENTROPY_BLOCKS-1; entropyIndex > 0; entropyIndex-- )
    {
        if(entropyIndex - bytesToShift >= 0)
        {
            entropyCache[entropyIndex] = entropyCache[entropyIndex-bytesToShift];
            entropyCache[entropyIndex] = entropyCache[entropyIndex] << bitsToShift;
            if(entropyIndex - bytesToShift -1 >= 0)
            {
                entropyCache[entropyIndex] = entropyCache[entropyIndex] | entropyCache[entropyIndex-bytesToShift -1 ] >> 8 - bitsToShift ;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }

    }
    
    for(uint8_t newEntropyIndex = 0; newEntropyIndex < bytesToShift - 2; newEntropyIndex++)
    {
        if(bytesToShift != newEntropyIndex)
        {
            entropyCache[newEntropyIndex] = newEntropy[newEntropyIndex];
        }
        else
        {
            if(bitsToShift != 0)
            {
                entropyCache[newEntropyIndex] = entropyCache[newEntropyIndex] | newEntropy[newEntropyIndex];
            }
            break;
        }
    }
    
    entropyCache[bytesToShift-1] = sourceNumber;
    entropyCache[bytesToShift-2] = newEntropySize;
    
    if (entropyLength >= MAX_ENTROPY_POOL_SIZE_BITS)
    {
        entropyLength = MAX_ENTROPY_POOL_SIZE_BITS;
    } else
    {
        entropyLength += entropySize;
    }
}

void Pool::clear()
{
    entropyLength=0x0; 
    for(uint8_t index = 0; index < ENTROPY_BLOCKS; index++)
    {
        entropyCache[index] = 0x0;
    }
}
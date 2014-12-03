#include "Pool.h"

Pool::Pool()
: entropyCache(0x0)
, entropyLength(0x0)
{

}

void Pool::addEntropy(uint32_t newEntropy, uint8_t entropySize)
{
    entropyCache = entropyCache << entropySize;
    entropyCache = entropyCache | newEntropy;
    if (entropyLength >= MAX_ENTROPY_POOL_SIZE)
    {
        entropyLength = MAX_ENTROPY_POOL_SIZE;
    } else
    {
        entropyLength += entropySize;
    }
}
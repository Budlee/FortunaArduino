#include "Pool.h"

Pool::Pool()
:entropyCache(0x0)
,entropyLength(0x0)
{
    
}

void Pool::addEntropy(uint32_t newEntropy, uint8_t entropySize)
{
    entropyCache = entropyCache << entropySize;
    entropyCache = entropyCache | newEntropy;
    entropyLength += entropySize;
}
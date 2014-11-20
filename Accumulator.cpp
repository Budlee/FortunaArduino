 #include "Accumulator.h"

Accumulator::Accumulator()
: generator(Generator())
, prngState(PRNGState(generator, POOL_SIZE))
{
    reseedTime = getTime();
}

uint8_t* Accumulator::RandomData()
{
    if(prngState.GetPoolData(0).length() > MIN_POOL_SIZE && reseedTime + 100 < getTime() )
    {
        
    }
    return generator.generateRandomData(16);
}

time_t Accumulator::getTime()
{
#if defined(ARDUINO) && ARDUINO >= 100 
    return getTimeNow();
#else
    time_t t;
    return time(&t);
#endif
}
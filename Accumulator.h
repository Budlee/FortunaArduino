#ifndef ACCUMULATOR_H
#define	ACCUMULATOR_H

#include <inttypes.h>
#include "Generator.h"
#include "PRNGState.h"

#if defined(ARDUINO) && ARDUINO >= 100 
#include <Time.h>
#else
#include <time.h>
#endif

#define POOL_SIZE 32
#define MIN_POOL_SIZE 64

class Accumulator
{
public:
    Accumulator();
    uint8_t* RandomData();
private:
    
    time_t getTime();
    time_t reseedTime;
    PRNGState prngState;
    Generator generator;
};

#endif	/* ACCUMULATOR_H */


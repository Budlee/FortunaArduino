#ifndef ACCUMULATOR_H
#define	ACCUMULATOR_H

#include "PRNGState.h"
#include "Source.h"
#include "SeedFile.h"
#include <inttypes.h>
#include <math.h>
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Time.h"
#include <Arduino.h>
#else
#include <time.h>
#include <stdlib.h>
#endif

#define POOL_COUNT 32
#define ENTROPY_SOURCE_MAX_SIZE 255
#define MIN_ENTROPY_POOL_SIZE 64

class Accumulator
{
public:
    Accumulator();
    ~Accumulator();
    //uint8_t* randomData(uint32_t numberOfBytes);
    bool registerEntropySource(Source *source);
    void addEventData(PRNGState *prngState);
    
private:
    struct SourceNodeStruct
    {
        int sourceNumber;
        Source *source;
        SourceNodeStruct *next;
    } *sourceNode;
    uint8_t sourceDeviceCount;
};

#endif	/* ACCUMULATOR_H */


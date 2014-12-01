#ifndef ACCUMULATOR_H
#define	ACCUMULATOR_H

#include <inttypes.h>
#include "PRNGState.h"
#include "Source.h"

#if defined(ARDUINO) && ARDUINO >= 100 
#include <Time.h>
#include <Arduino.h>
#else
#include <time.h>
#include <stdlib.h>
#endif

#define ENTROPY_SOURCE_MAX_SIZE 255
#define MIN_POOL_SIZE 32

class Accumulator
{
public:
    Accumulator();
    ~Accumulator();
    uint8_t* RandomData(u_int16_t numberOfBytes);
    bool registerEntropySource(Source *source);
    void AddEventData();
private:
    struct SourceNodeStruct
    {
        int sourceNumber;
        Source *source;
        SourceNodeStruct *next;
    } *sourceNode;
    
    time_t getTime();
    time_t reseedTime;
    PRNGState prngState;
    uint8_t sourceDeviceCount;
    Sha256Class sha;
    uint8_t *poolEntropy;// = new uint8_t[32 * poolUsageCount];
};

#endif	/* ACCUMULATOR_H */


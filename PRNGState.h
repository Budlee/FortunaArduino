#ifndef PRNGSTATE_H
#define	PRNGSTATE_H

#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100 
#include <String.h>
typedef String String;
#else
#include <string>
typedef std::string String;
#endif


#include "Generator.h"

class PRNGState {
public:
    PRNGState(Generator inGen, uint8_t poolCount);
    String GetPoolData(uint8_t poolNumber);
private:
    String* pools;
    uint16_t reseedCount;
    Generator generator;

};

#endif	/* PRNGSTATE_H */


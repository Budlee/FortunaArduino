#ifndef FORTUNA_H
#define	FORTUNA_H

#include "Accumulator.h"
#include "SeedFile.h"
#include <inttypes.h>

/**
 * Seed file is optional. The reason is that I think it is useful to have but
 * could leave the device open to more side channel attacks. Hence I have made
 * it optional.
 */

class Fortuna {
public:
    Fortuna();
    Fortuna(SeedFile *seedFile);
    bool registerSource(Source *source);
    void gatherEntropy(){accumulator.addEventData(&prngState);}
    /*
     * return NULL on no random data
     */
    uint8_t* getRandomData(uint32_t byteSize);
    
private:
    Accumulator accumulator;
    PRNGState prngState;
    time_t reseedTime;
    time_t getTime();
    SeedFile *seedFile;
    bool seedFileReseed;
    Sha256Class sha;
    uint8_t *poolEntropy;
};
#endif	/* FORTUNA_H */


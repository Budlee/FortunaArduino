/* 
 * File:   SeedFile.h
 * Author: matt
 *
 * Created on 17 December 2014, 09:53
 */

#ifndef SEEDFILE_H
#define	SEEDFILE_H

#include<inttypes.h>
#define SEED_FILE_SIZE 128

class SeedFile
{
public:
    virtual bool firstTimeAccess() = 0;
    virtual uint8_t* readSeedFile() = 0;
    virtual void writeSeedFile(uint8_t *seed) = 0;
    
private:
    
};

#endif	/* SEEDFILE_H */


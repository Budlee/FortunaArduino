/* 
 * File:   LinuxSeedFileManager.h
 * Author: matt
 *
 * Created on 17 December 2014, 10:31
 */

#ifndef LINUXSEEDFILEMANAGER_H
#define	LINUXSEEDFILEMANAGER_H

#ifndef ARDUINO

#define SEED_FILE "./seedfile"

#include <inttypes.h>
#include "SeedFile.h"


class LinuxSeedFileManager: public SeedFile {
public:
    LinuxSeedFileManager();
    uint8_t* readSeedFile();
    void writeSeedFile(uint8_t *seed);
    bool firstTimeAccess(){return fTimeAccess;}
private:
    bool fTimeAccess;
    uint8_t *seedData;
};

#endif
#endif	/* LINUXSEEDFILEMANAGER_H */


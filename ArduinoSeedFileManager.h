/* 
 * File:   ArduinoSeedFileManager.h
 * Author: matt
 *
 * Created on 17 December 2014, 13:00
 */

#ifndef ARDUINOSEEDFILEMANAGER_H
#define	ARDUINOSEEDFILEMANAGER_H

#if defined(ARDUINO) && ARDUINO >= 100 
 #include <Arduino.h>
 #include <EEPROM.h>


#define START_OF_SEED 383 //511-128
#define FIRST_ACCESS_ADDRESS 382

#include <inttypes.h>
#include "SeedFile.h"

class ArduinoSeedFileManager: public SeedFile {
public:
    ArduinoSeedFileManager();
    uint8_t* readSeedFile();
    void writeSeedFile(uint8_t *seed);
    bool firstTimeAccess(){return fTimeAccess;}
    
private:
    bool fTimeAccess;
    uint8_t *seedData;
};

#endif

#endif	/* ARDUINOSEEDFILEMANAGER_H */


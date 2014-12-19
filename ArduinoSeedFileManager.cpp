/* 
 * File:   ArduinoSeedFileManager.cpp
 * Author: matt
 * 
 * Created on 17 December 2014, 13:00
 */

#if defined(ARDUINO) && ARDUINO >= 100 

#include "ArduinoSeedFileManager.h"

ArduinoSeedFileManager::ArduinoSeedFileManager()
{
    if(EEPROM.read(FIRST_ACCESS_ADDRESS) != 0x01)
    {
        fTimeAccess = true;
    }
    else
    {
        fTimeAccess = false;
    }
    
}

uint8_t* ArduinoSeedFileManager::readSeedFile()
{
    if(fTimeAccess)
    {
        return NULL;
    }
    seedData = new uint8_t[SEED_FILE_SIZE];
    for(uint8_t eepromIndex = 0; eepromIndex < SEED_FILE_SIZE; eepromIndex++)
    {
        seedData[eepromIndex] = EEPROM.read(START_OF_SEED+eepromIndex);
    }
    return seedData;
}

void ArduinoSeedFileManager::writeSeedFile(uint8_t* seed)
{
    if(fTimeAccess)
    {
        EEPROM.write(FIRST_ACCESS_ADDRESS, 0x01);
        fTimeAccess = false;
    }
    for(uint8_t eepromIndex = 0; eepromIndex < SEED_FILE_SIZE; eepromIndex++)
    {
         EEPROM.write(START_OF_SEED+eepromIndex, seed[eepromIndex]);
    }
}

#endif
/* 
 * File:   LinuxSeedFileManager.cpp
 * Author: matt
 * 
 * Created on 17 December 2014, 10:31
 */

#ifndef ARDUINO

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ios>

#include "LinuxSeedFileManager.h"

LinuxSeedFileManager::LinuxSeedFileManager()
{
    if(access(SEED_FILE,F_OK|R_OK|W_OK) == -1)
    {
        fTimeAccess = true;
        FILE *file = fopen(SEED_FILE,"a");
        fclose(file);
    }
    else
    {
        fTimeAccess = false;
    }
    
}

uint8_t* LinuxSeedFileManager::readSeedFile()
{
    if(fTimeAccess == true)
    {
        return NULL;
    }
    seedData = new uint8_t[SEED_FILE_SIZE];
    FILE *file = fopen(SEED_FILE,"r");
    fread(seedData,sizeof(uint8_t),SEED_FILE_SIZE, file);
    fclose(file);
    return seedData;
}

void LinuxSeedFileManager::writeSeedFile(uint8_t* seed)
{
    fTimeAccess = false;
    FILE *file = fopen(SEED_FILE,"w");
    fwrite(seed,sizeof(uint8_t), SEED_FILE_SIZE, file);
    fclose(file);
}

#endif
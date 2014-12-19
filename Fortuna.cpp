#include "Fortuna.h"

Fortuna::Fortuna()
: accumulator(Accumulator())
,prngState(PRNGState())
, seedFile(NULL)
, seedFileReseed(true)
{
    reseedTime = getTime();
}

Fortuna::Fortuna(SeedFile *inSeedFile)
: accumulator(Accumulator())
, prngState(PRNGState())
, seedFile(inSeedFile)
, seedFileReseed(false)
{
    if (!seedFile->firstTimeAccess())
    {
        uint8_t *seedData = seedFile->readSeedFile();
        prngState.reseed(seedData, SEED_FILE_SIZE);
        delete[] seedData;
    }
    reseedTime = getTime();
}

bool Fortuna::registerSource(Source *source)
{
    accumulator.registerEntropySource(source);
}

uint8_t* Fortuna::getRandomData(uint32_t numberOfBytes)
{
    //TODO: This needs to be changed as time is in seconds NOT mili seconds so should check reseed every 100mS not every 1000mS
    if (prngState.getPool(0)->length() >= MIN_ENTROPY_POOL_SIZE && reseedTime + 1 < getTime())
    {
        uint16_t reseedCount = prngState.getReseedCount() + 1;
        uint8_t poolUsageCount = 0;

        for (uint8_t poolIndex = 0; poolIndex < prngState.getPoolSize(); poolIndex++)
        {
            double dRC = reseedCount;
            double dPI = poolIndex;
            double ans = fmod(dRC, pow(2.0, dPI));
            if (ans == 0)
            {
                ++poolUsageCount;
            } else
            {
                break;
            }
        }
        /*
         * This is something that I am not keen on doing, however, I think with the 
         * structure this is the only way of doing this. When 128 bits of entropy
         * are gathered instead of using it for the reseed of the generator it is
         * instead to be used to re-write the seed file.
         * 1. It means FORTUNA can continue to work and the data will still be random
         * based on the use if the previous reseeded key
         * 2. The only other way is to retrieve the first 128bits of entropy to put
         * back into the seed file. If the seed file has been compromised this will 
         * mean that the first reseed will purt FORTUNA
         * into an unkown state again.
         *  
         */
        if (MIN_ENTROPY_POOL_SIZE * poolUsageCount >= 128 && seedFile && !seedFileReseed)
        {
            uint8_t *seed = new uint8_t[128];
            for (uint8_t poolIndex = 0; poolIndex < poolUsageCount; poolIndex++)
            {
                uint8_t *entropyArray = prngState.getPool(poolIndex)->getEntropy();
                for (uint8_t entropyIndex = 0; entropyIndex < ENTROPY_BLOCKS; entropyIndex++)
                {
                    //TODO:VALIDATE THAT THIS puts the entropy in the correct place
                    seed[(poolIndex * MIN_ENTROPY_POOL_SIZE) + entropyIndex] = entropyArray[entropyIndex];
                }
            }
            seedFile->writeSeedFile(seed);
            delete[] seed;
            seedFileReseed = true;
        }
        else
        {
            poolEntropy = new uint8_t[HASH_LENGTH * poolUsageCount];
            for (uint8_t poolIndex = 0; poolIndex < poolUsageCount; poolIndex++)
            {
                sha.init();
                uint8_t *entropyArray = prngState.getPool(poolIndex)->getEntropy();
                for (uint8_t entropyIndex = 0; entropyIndex < ENTROPY_BLOCKS; entropyIndex++)
                {
                    sha.write(entropyArray[entropyIndex]);
                }
                uint8_t* shaResult = sha.result();
                #if defined(ARDUINO) && ARDUINO >= 100 
                    memcpy(poolEntropy + (32 * poolIndex), shaResult, 32);
                #else
                    std::copy(shaResult, shaResult + 32, poolEntropy + (POOL_SIZE * poolIndex));
                #endif
                prngState.getPool(poolIndex)->clear();
            }
            prngState.reseed(poolEntropy, POOL_SIZE * poolUsageCount);
            delete[] poolEntropy;
        }
        reseedTime = getTime();
    }
    uint8_t *randomBytes = new uint8_t[numberOfBytes];
    return prngState.generateRandomData(numberOfBytes, randomBytes);

}


time_t Fortuna::getTime()
{
#if defined(ARDUINO) && ARDUINO >= 100 
    return now();
#else
    time_t t;
    return time(&t);
#endif
}



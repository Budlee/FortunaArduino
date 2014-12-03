#include "Generator.h"


Generator::Generator()
: generatorState(GeneratorState())
,cipherText(new uint8_t[16])
,aesPlainText( new uint8_t[N_BLOCK])
{

}

Generator::~Generator()
{
    delete[] cipherText;
    delete[] aesPlainText;
}

void Generator::reseedGenerator(uint8_t* seed, uint16_t seedSize)
{
    	uint16_t newKeySize = seedSize+generatorState.getKeySize();
    	uint8_t *newKey = new uint8_t[newKeySize]; // create new key to be hashed
        
        //K ← SHAd-256(K || s) <--- (This is stright out of Bruce Schneier and Neils Fergusons Practical Cryptography)
        #if defined(ARDUINO) && ARDUINO >= 100 
            memcpy_P(newKey, generatorState.getKey(), generatorState.getKeySize());
            memcpy_P(newKey + generatorState.getKeySize(), seed, seedSize);
        #else
            std::copy(generatorState.getKey(), generatorState.getKey() + generatorState.getKeySize(), newKey);
            std::copy(seed, seed + seedSize, newKey + generatorState.getKeySize());
        #endif
    	sha.init();
    	sha.write(*newKey);
        uint8_t *shaResult = sha.result();
    	generatorState.setKey(shaResult, 32);
    	generatorState.addToCounter();
        delete[] newKey;
}

uint8_t* Generator::generateRandomData(uint32_t numberOfBytes, u_int8_t *randomBytes)
{
    if (numberOfBytes >= 1 && numberOfBytes < pow(2.0,20.0))
    {
        uint8_t rNoB = ceil(numberOfBytes / 16.0);
        uint8_t *random16kBytes = new uint8_t[rNoB * 16];
        if (generateBlocks(rNoB, random16kBytes))
        {
            #if defined(ARDUINO) && ARDUINO >= 100 
                memcpy_P(randomBytes, random16kBytes, numberOfBytes);
            #else
                std::copy(random16kBytes, random16kBytes + numberOfBytes, randomBytes);
            #endif
            uint8_t *newKey = new uint8_t[2 * 16];
            generateBlocks(2, newKey);
            generatorState.setKey(newKey, 32);
            delete[] newKey;
        }
        delete[] random16kBytes;
    }
    return randomBytes;
}

bool Generator::generateBlocks(uint8_t numberOfBlocks, uint8_t* pseudroRandomData)
{
    if (numberOfBlocks >= 1 && !generatorState.isZeroCount())
    {
        uint8_t *keyPtr = generatorState.getKey();
        aes.clean();
        aes.set_key(keyPtr, generatorState.getKeySize());
        for (uint8_t index = 0; index < numberOfBlocks; index++)
        {
            uint8_t *v = generatorState.getCount();
            for(uint8_t indexCounter = 0; indexCounter <N_BLOCK ; indexCounter++)
            {
                aesPlainText[indexCounter] = v[indexCounter]; 
            }
            aes.encrypt(aesPlainText, cipherText);
            generatorState.addToCounter();
            #if defined(ARDUINO) && ARDUINO >= 100 
                memcpy_P(pseudroRandomData, cipherText + (16 * index), 16);
            #else
                std::copy(cipherText, cipherText + 16, pseudroRandomData + (16 * index));
            #endif
        }
        return 1;
    }
    return 0;
}

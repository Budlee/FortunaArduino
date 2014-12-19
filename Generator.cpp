#include "Generator.h"

Generator::Generator()
: generatorState(GeneratorState())
, cipherText(new uint8_t[16])
, aesPlainText(new uint8_t[N_BLOCK])
{

}

Generator::~Generator()
{
    delete[] cipherText;
    delete[] aesPlainText;
}

void
Generator::reseedGenerator(uint8_t* seed, uint16_t seedSize)
{
    uint16_t newKeySize = seedSize + generatorState.getKeySize();
    uint8_t *newKey = new uint8_t[newKeySize]; // create new key to be hashed

    //K ← SHAd-256(K || s) <--- (This is stright out of Bruce Schneier and Neils Fergusons Practical Cryptography)
    #if defined(ARDUINO) && ARDUINO >= 100 
    memcpy(newKey, generatorState.getKey(), generatorState.getKeySize());
    memcpy(newKey + generatorState.getKeySize(), seed, seedSize);
    #else
    std::copy(generatorState.getKey(), generatorState.getKey() + generatorState.getKeySize(), newKey);
    std::copy(seed, seed + seedSize, newKey + generatorState.getKeySize());
    #endif
    sha.init();
    for (uint16_t keyIndex = 0; keyIndex < newKeySize; keyIndex++)
    {
        sha.write(newKey[keyIndex]);
    }
    uint8_t *shaResult = sha.result();
    generatorState.setKey(shaResult, 32);
    generatorState.addToCounter();
    delete[] newKey;
}

uint8_t*
Generator::generateRandomData(uint32_t numberOfBytes, uint8_t *randomBytes)
{
    /* 
     * This should be in generateBlocks. However, for this I have put it here otherwise
     * it will harm performance with isZeroCount() being called exessive times
     */
    if (generatorState.isZeroCount())
    {
        delete[] randomBytes;
        randomBytes = NULL;
        return randomBytes;
    }
    if (numberOfBytes >= 1 && numberOfBytes < 1048576) //1048576 = 2^20
    {
        uint8_t rNoB = ceil(numberOfBytes / 16.0);
        uint8_t *random16kBytes = new uint8_t[rNoB * 16];
        if (generateBlocks(rNoB, random16kBytes))
        {
            #if defined(ARDUINO) && ARDUINO >= 100 
            memcpy(randomBytes, random16kBytes, numberOfBytes);
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
    //    if (numberOfBlocks >= 1 && !generatorState.isZeroCount())
    if (numberOfBlocks >= 1)
    {
        uint8_t *keyPtr = generatorState.getKey();
        aes.clean();
        aes.set_key(keyPtr, generatorState.getKeySize());
        for (uint8_t index = 0; index < numberOfBlocks; index++)
        {
            uint8_t *v = generatorState.getCount();
            for (uint8_t indexCounter = 0; indexCounter < MAX_COUNTER_SIZE; indexCounter++)
            {
                aesPlainText[indexCounter] = v[indexCounter];
            }
            aes.encrypt(aesPlainText, cipherText);
            generatorState.addToCounter();
            #if defined(ARDUINO) && ARDUINO >= 100 
            memcpy(pseudroRandomData + (16 * index), cipherText, 16);
            #else
            std::copy(cipherText, cipherText + 16, pseudroRandomData + (16 * index));
            #endif
        }
        return 1;
    }
    return 0;
}

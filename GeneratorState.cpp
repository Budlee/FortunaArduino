#include "GeneratorState.h"
#include "Generator.h"

GeneratorState::GeneratorState()
:keySize(0x00)
,key(new uint8_t[0])
,counter(new uint8_t[MAX_COUNTER_SIZE])
{
    for(uint8_t i = 0; i< MAX_COUNTER_SIZE; i++)
    {
        counter[i] = 0x00;
    }
}

void GeneratorState::setKey(uint8_t *newKey, uint8_t newKeySize)
{
    keySize = newKeySize;
    delete[] key;
    key = new uint8_t[newKeySize];
#if defined(ARDUINO) && ARDUINO >= 100 
    memcpy(key, newKey, newKeySize);
#else
    std::copy(newKey, newKey + newKeySize, key);
#endif
}

bool GeneratorState::isZeroCount()
{
    for(uint8_t index = 0; index < MAX_COUNTER_SIZE; index++)
    {
        if(counter[index] != 0x00)
        {
            return 0;
        }
    }
    return 1;
}

void GeneratorState::addToCounter()
{
    for(uint8_t index = MAX_COUNTER_SIZE; index > 0; index--)
    {
        if(counter[index-1] == 0xFF)
        {
           counter[index-1] = 0x00;
           continue; 
        }
        else
        {
            counter[index-1]++;
            return;
        }
    }
}
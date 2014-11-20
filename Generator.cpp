#include <stdlib.h>

#include "Generator.h"

Generator::Generator()
:generatorState(GeneratorState())
{

}

void Generator::reseedGenerator(uint8_t* seed, uint8_t seedSize)
{
//	uint8_t newKeySize = seedSize+generatorState.getKeySize();
//	uint8_t *newKey = (uint8_t*)malloc(sizeof(uint8_t)*(newKeySize)); // create new key to be hashed
//    
//    memcpy(newKey, generatorState.getKey(), generatorState.getKeySize());
//    memcpy(newKey + generatorState.getKeySize(), seed, seedSize);
//    
//    Sha256 sha;
//	sha.init();
//	sha.write(*newKey);
//	generatorState.setKey(sha.result());
//    generatorState.setKeySize(32);
//	generatorState.addToCounter();	
}

uint8_t* Generator::generateRandomData(uint8_t numberOfBytes)
{
    u_int8_t *randomBytes = new uint8_t[numberOfBytes];
    if(numberOfBytes > 1)
    {
        for(uint8_t index = 0; index < numberOfBytes ; index++)
        {
            
            generatorState.addToCounter();
        }
    }
    return randomBytes; 
}


bool Generator::generateBlocks(uint8_t numberOfBlocks, uint8_t* pseudroRandomData)
{
    u_int8_t *randomBytes = new uint8_t[numberOfBlocks];
    if(numberOfBlocks > 1 && generatorState.getReseedCount() != 0)
    {
        for(uint8_t index = 0; index < numberOfBlocks ; index++)
        {
            //AES aes;
            generatorState.addToCounter();
        }
    }
    return randomBytes; 
    
    
    
    
//	if(!generatorState.getReseedCount() || numberOfBlocks < MAX_BLOCK_GENERATE_SIZE)
//	{
//		return 0;
//	}
//	AES aes;
//	aes.set_key(generatorState.getKey(), generatorState.getKeySize());
//	for(uint8_t index = 0 ; index < numberOfBlocks ; index++)
//	{
//		aes.encrypt(plainText, cipherText);
//		for(uint8_t j = 0 ; j < 16; j ++)
//		{
//			pseudroRandomData[(index*16)+j] = cipherText[j];
//		}
//		generatorState.addToCounter();
//	}
//	//Just to be safe clear plainText and cipherText
//	for(uint8_t j = 0 ; j < 16; j ++)
//	{
//		plainText[0] = 0;
//		cipherText[0] = 0;
//	}
   return 1; 
}

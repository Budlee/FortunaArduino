#include "PRNGState.h"

PRNGState::PRNGState(Generator inGen, uint8_t poolCount)
:generator(inGen)
,reseedCount(0)
,pools(new String[poolCount])
{
}

String PRNGState::GetPoolData(uint8_t poolNumber)
{
    String *ptrPool = pools + poolNumber;
    return *ptrPool;
}
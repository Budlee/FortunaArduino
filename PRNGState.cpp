#include "PRNGState.h"

PRNGState::PRNGState()
:generator(Generator())
,pools(new Pool[POOL_SIZE])
,reseedCount(0x00)
{
}


PRNGState::~PRNGState()
{
    delete[] pools;
}

Pool* PRNGState::getPool(uint8_t poolNumber)
{
    if(poolNumber >= POOL_SIZE)
    {
        return NULL;
    }
    return &pools[poolNumber];
}
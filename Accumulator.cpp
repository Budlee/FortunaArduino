#include "Accumulator.h"

Accumulator::Accumulator()
: prngState(PRNGState())
, sourceNode(NULL)
, sourceDeviceCount(0x0)
{
    reseedTime = getTime();
}

Accumulator::~Accumulator()
{
    if (sourceNode != NULL)
    {
        if (sourceNode->next != NULL)
        {
            SourceNodeStruct *sourceNodeNext;
            do
            {
                sourceNodeNext = sourceNode->next;
                delete sourceNode;
                sourceNode = sourceNodeNext;
            } while (sourceNode != NULL);
        }
        else
        {
            delete sourceNode;
        }
    }
}

uint8_t* Accumulator::RandomData(uint32_t numberOfBytes)
{
    //TODO: This needs to be changed as time is in seconds NOT mili seconds so should check reseed every 100mS not every 1000mS
    if (prngState.getPool(0)->length() >= MIN_ENTROPY_POOL_SIZE && reseedTime + 1 < getTime())
    {
        uint16_t reseedCount = prngState.getReseedCount() + 1;
        uint8_t poolUsageCount = 0;

        /*
         * YES I know this is not efficent and should a linked list or something.
         * However in this case I just run through the pools we will use just to save a 
         * bit of dev time
         */
        for (uint8_t poolIndex = 0; poolIndex < prngState.getPoolSize(); poolIndex++)
        {
            #if defined(ARDUINO) && ARDUINO >= 100 
                float fRC = reseedCount;
                float fPI = poolIndex;
                double ans = fRC/pow(2,fPI);
            #else
                double dRC = reseedCount;
                double dPI = poolIndex;
                double ans = dRC/pow(2,dPI);
            #endif
            if (ans >= 1)
            {
                ++poolUsageCount;
            } else
            {
                break;
            }
        }
        
        poolEntropy = new uint8_t[32 * poolUsageCount];
        for (u_int8_t poolIndex = 0; poolIndex < poolUsageCount; poolIndex++)
        {
            sha.init();
            uint32_t v = prngState.getPool(poolIndex)->getEntropy();
            sha.write(v);
            uint8_t* shaResult = sha.result();
            #if defined(ARDUINO) && ARDUINO >= 100 
                memcpy_P(poolEntropy + (32 * poolIndex), shaResult, 32);
            #else
                std::copy(shaResult, shaResult+32, poolEntropy + (32*poolIndex));
            #endif
            prngState.getPool(poolIndex)->clear();
        }
        prngState.reseed(poolEntropy, 32*poolUsageCount);
        delete[] poolEntropy;
        reseedTime = getTime();
    }
    uint8_t *randomBytes = new uint8_t[numberOfBytes];
    return prngState.generateRandomData(numberOfBytes, randomBytes);
}

bool Accumulator::registerEntropySource(Source *source)
{
    if (sourceDeviceCount <= 255)
    {
        if (sourceNode)
        {
            SourceNodeStruct *sourceNodeCpy = sourceNode;
            while (sourceNodeCpy->next)
            {
                sourceNodeCpy = sourceNodeCpy->next;
            }
            SourceNodeStruct *newSourceNode = new SourceNodeStruct();
            newSourceNode->source = source;
            newSourceNode->sourceNumber = sourceDeviceCount++;
            newSourceNode->next = NULL;
            sourceNodeCpy->next = newSourceNode;
        } else
        {
            //First entry
            sourceNode = new SourceNodeStruct;
            sourceNode->source = source;
            sourceNode->sourceNumber = sourceDeviceCount++;
            sourceNode->next = NULL;
        }
        return 1;
    }
    return 0;
}

void Accumulator::AddEventData()
{
    SourceNodeStruct *sourceNodeCopy = sourceNode;
    for (uint8_t sourceIndex = 0; sourceIndex < sourceDeviceCount; sourceIndex++)
    {
        uint8_t poolNumber = 0;
        uint8_t entropySize = 0;
        uint8_t *entropy = sourceNodeCopy->source->getEntropy(&poolNumber, &entropySize);
        prngState.getPool(poolNumber)->addEntropy(*entropy, entropySize);
        sourceNodeCopy = sourceNodeCopy->next;
    }
}

time_t Accumulator::getTime()
{
#if defined(ARDUINO) && ARDUINO >= 100 
    return getTimeNow();
#else
    time_t t;
    return time(&t);
#endif
}
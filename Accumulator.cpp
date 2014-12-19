#include "Accumulator.h"

Accumulator::Accumulator()
: sourceNode(NULL)
, sourceDeviceCount(0x0)
{
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
        } else
        {
            delete sourceNode;
        }
    }
}

bool Accumulator::registerEntropySource(Source *source)
{
    if (sourceDeviceCount <= 255)
    {
        source->setSourceId(sourceDeviceCount);
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

void Accumulator::addEventData(PRNGState *prngState)
{
    SourceNodeStruct *sourceNodeCopy = sourceNode;
    for (uint8_t sourceIndex = 0; sourceIndex < sourceDeviceCount; sourceIndex++)
    {
        uint8_t poolNumber = 0;
        uint8_t entropySize = 0;
        uint8_t *entropy = sourceNodeCopy->source->getEntropy(&poolNumber, &entropySize);
        prngState->getPool(poolNumber)->addEntropy(entropy, entropySize, sourceNodeCopy->source->getSourceNumber());
        sourceNodeCopy = sourceNodeCopy->next;
    }
}
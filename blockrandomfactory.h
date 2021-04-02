#ifndef BLOCKRANDOMFACTORY_H
#define BLOCKRANDOMFACTORY_H

#include "blockfactory.h"

class Block;

class BlockRandomFactory : public BlockFactory
{
public:
    BlockRandomFactory();

    Block * getBlock();
};

#endif // BLOCKRANDOMFACTORY_H

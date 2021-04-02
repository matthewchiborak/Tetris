#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <QPoint>

class Block;

class BlockFactory
{
public:
    BlockFactory();

    virtual Block * getBlock();
};

#endif // BLOCKFACTORY_H

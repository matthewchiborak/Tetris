#include "blockrandomfactory.h"

#include <QRandomGenerator>
#include "block.h"

BlockRandomFactory::BlockRandomFactory()
{

}

Block *BlockRandomFactory::getBlock()
{
    //Randomly select one of the 7 tetris shapes
    int randomValue = QRandomGenerator::global()->bounded(7);

    Block * blockToReturn;

    //Piece spawn location. 4, 20?
    QPoint location(4, 20);

    switch(randomValue)
    {
    case 0:
        //Problem with spawning I block. Will need to spawn it one block lower than the rest
        //(See reference image)
        location.setY(location.y() - 1);
        blockToReturn = new BlockI(location);
        break;
    case 1:
        blockToReturn = new BlockO(location);
        break;
    case 2:
        blockToReturn = new BlockT(location);
        break;
    case 3:
        blockToReturn = new BlockS(location);
        break;
    case 4:
        blockToReturn = new BlockZ(location);
        break;
    case 5:
        blockToReturn = new BlockJ(location);
        break;
    default:
        blockToReturn = new BlockL(location);
        break;
    }

    return blockToReturn;
}

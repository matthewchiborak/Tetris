#include "boardmodel.h"

#include "block.h"

#include <QDebug>

BoardModel::BoardModel()
    : m_lineClears(0),
      m_currentMovingBlock(new BlockNull()),
      m_nextBlock(new BlockNull()),
      m_holdBlock(new BlockNull()),
      m_currentGravity(1000),
      m_ignoreGameOverCheck(false)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            m_gameGridFillState[i][j] = false;
        }
    }
}

void BoardModel::addBlock(Block *blockToAdd)
{
    m_blocks.push_back(blockToAdd);
}

void BoardModel::setBlockInPlace(Block *blockToSet)
{
    foreach(QPoint focusPoint, blockToSet->getBlockPoints())
    {
        m_gameGridFillState[focusPoint.x()][focusPoint.y()] = true;
    }
}

bool BoardModel::checkIfOutOfBoundsOrOverlapBlock(QList<QPoint> *points)
{

    foreach (QPoint focusPoint, *points)
    {
        //Check if would go out of bounds
        if(((focusPoint.x()) < 0) || ((focusPoint.x()) > 9))
        {
            return false;
        }

        //Check if hit floor
        if((focusPoint.y()) < 0)
        {
            return false;
        }

        //Check if hit any set pieces
        if(m_gameGridFillState[focusPoint.x()][focusPoint.y()])
        {
            //A block is already in the space, can't do it
            return false;
        }
    }

    return true;
}

void BoardModel::dropAllRowsAbove(int row)
{
    for(int i = 0; i < m_blocks.length(); i++)
    {
        m_blocks.at(i)->dropOneBlockIfAnyBlockIsAboveRow(row);
    }

    for(int r = row; r < 19; r++)
    {
        for(int c = 0; c < 10; c++)
        {
            m_gameGridFillState[c][r] = m_gameGridFillState[c][r+1];
            m_gameGridFillState[c][r+1] = false;
        }
    }
}

void BoardModel::clearRow(int row)
{
    //foreach(Block * focusBlock, m_blocks)
    for(int i = 0 ; i < m_blocks.length(); i++)
    {
        Block * focusBlock = m_blocks.at(i);

        if(focusBlock->removeAnyBlockPointsOnRow(row) <= 0)
        {
            delete focusBlock;
            m_blocks.removeAt(i);
            i--;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        m_gameGridFillState[i][row] = false;
    }
}

void BoardModel::draw(QPainter *p)
{
    QBrush brush;

    foreach(Block* focusBlock, m_blocks)
    {
        focusBlock->draw(p);
    }
}

bool BoardModel::canMove(Block *blockToCheck, QPoint direction)
{
    QList<QPoint> blockPoints = blockToCheck->getBlockPoints();
    QList<QPoint> testPoints;

    foreach (QPoint focusPoint, blockPoints)
    {
        QPoint newPoint(focusPoint.x() + direction.x(), focusPoint.y() + direction.y());
        testPoints.push_back(newPoint);
    }

    return checkIfOutOfBoundsOrOverlapBlock(&testPoints);
}

bool BoardModel::moveCurrentBlock(QPoint direciton)
{
    if(canMove(m_currentMovingBlock, direciton))
    {
        m_currentMovingBlock->move(direciton);
        return true;
    }

    return false;
}

void BoardModel::addNewPieceForTheBoardForPlayerToUse(Block *newBlock)
{
    m_currentMovingBlock = m_nextBlock;
    m_nextBlock = newBlock;

    addBlock(m_currentMovingBlock);
}

void BoardModel::initPieces(Block *firstBlock, Block *nextBlock)
{
    m_currentMovingBlock = firstBlock;
    m_nextBlock = nextBlock;

    addBlock(m_currentMovingBlock);
}

void BoardModel::setCurrentBlockInPlace()
{
    setBlockInPlace(m_currentMovingBlock);
}

void BoardModel::dropCurrentBlock()
{
    QPoint dir(0, -1);

    while(canMove(m_currentMovingBlock, dir))
    {
        m_currentMovingBlock->move(dir);
    }
}

bool BoardModel::canRotate(Block *blockToCheck)
{
    QList<QPoint> postRotPoints = blockToCheck->getPointsIfWereToRotate();

    return checkIfOutOfBoundsOrOverlapBlock(&postRotPoints);
}

void BoardModel::rotateCurrentBlock()
{
    //Check if can rotate
    if(canRotate(m_currentMovingBlock))
    {
        m_currentMovingBlock->rotate();
    }
}

void BoardModel::checkAndCleanUpLines()
{
    for(int r = 0; r < 20; r++)
    {
        int rowCount = 0;
        for(int c = 0; c < 10; c++)
        {
            if(m_gameGridFillState[c][r])
                rowCount++;
        }

        if(rowCount >= 10)
        {
            //A line was cleared you can ignore gameover
            setIgnoreGameOverCheck(true);

            clearRow(r);
            dropAllRowsAbove(r);
            r--;
            incrementLineClears();
        }
    }
}

int BoardModel::getNumberOfLineClears()
{
    return m_lineClears;
}

void BoardModel::incrementLineClears()
{
    m_lineClears++;
}

Block *BoardModel::getCurrentBlock()
{
    return m_currentMovingBlock;
}

Block *BoardModel::getNextBlock()
{
    return m_nextBlock;
}

Block *BoardModel::getHoldBlock()
{
    return m_holdBlock;
}

QMutex *BoardModel::getMutex()
{
    return &m_modelMutex;
}

void BoardModel::holdBlock()
{
    // Other wise just swap them

    m_blocks.removeLast();

    //Update the position of the hold block

    Block * temp = m_holdBlock;

    m_holdBlock = m_currentMovingBlock;
    m_currentMovingBlock = temp;

    m_currentMovingBlock->setPosition(m_holdBlock->getPosition());
    m_holdBlock->setPosition(QPoint(0,0));

    addBlock(m_currentMovingBlock);
}

bool BoardModel::checkAndDeleteCurrentBlockIfNull()
{
    if(m_currentMovingBlock->getBlockPoints().length() <= 0)
    {
        deleteCurrentBlock();
        return true;
    }

    return false;
}

void BoardModel::setGravityBasedOnLineClears()
{
    int newGravity = (1000 - (m_lineClears*10));
    if(newGravity < 100)
        newGravity = 100;
    m_currentGravity = newGravity;
}

int BoardModel::getGravity()
{
    return m_currentGravity;
}

void BoardModel::setIgnoreGameOverCheck(bool value)
{
    m_ignoreGameOverCheck = value;
}

bool BoardModel::getIgnoreGameOverCheck()
{
    return m_ignoreGameOverCheck;
}

void BoardModel::deleteCurrentBlock()
{
    m_blocks.removeLast();
    Block * temp = m_currentMovingBlock;
    m_currentMovingBlock = nullptr;
    delete temp;
}

//Block *BoardModel::getCurrentMovingBlock()
//{
//    return m_currentMovingBlock;
//}


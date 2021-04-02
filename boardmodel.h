#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QMutex>

class Block;

class BoardModel
{
public:
    BoardModel();

    void draw(QPainter * p);
    bool canMove(Block * blockToCheck, QPoint direction);
    bool moveCurrentBlock(QPoint direciton); //True on suscessmove, false on failed move

    void addNewPieceForTheBoardForPlayerToUse(Block * newBlock);
    void initPieces(Block * firstBlock, Block * nextBlock);

    void setCurrentBlockInPlace();
    void dropCurrentBlock();
    bool canRotate(Block * blockToCheck);
    void rotateCurrentBlock();

    void checkAndCleanUpLines();

    int getNumberOfLineClears();
    void incrementLineClears();

    Block * getCurrentBlock();
    Block * getNextBlock();
    Block * getHoldBlock();

    QMutex * getMutex();

    //Will hold the block or swap the blocks if hold block isn't null
    void holdBlock();
    bool checkAndDeleteCurrentBlockIfNull();

    void setGravityBasedOnLineClears();
    int getGravity();

    void setIgnoreGameOverCheck(bool value);
    bool getIgnoreGameOverCheck();


private:
    void addBlock(Block * blockToAdd);
    void setBlockInPlace(Block * blockToSet);

    bool checkIfOutOfBoundsOrOverlapBlock(QList<QPoint> * points);
    void dropAllRowsAbove(int row);
    void clearRow(int row);

    void deleteCurrentBlock();

    //10 wide, 20 high. 0,0 is the bottom left corner
    bool m_gameGridFillState[10][20];

    Block * m_currentMovingBlock;
    Block * m_nextBlock;
    Block * m_holdBlock;
    QList<Block*> m_blocks;
    QMutex m_modelMutex;

    int m_currentGravity;

    int m_lineClears;

    bool m_ignoreGameOverCheck;
};

#endif // BOARDMODEL_H

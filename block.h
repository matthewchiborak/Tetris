#ifndef BLOCK_H
#define BLOCK_H

#include <QPoint>
#include <QColor>
#include <QPainter>

class Block
{
public:
    Block();
    void draw(QPainter *p);
    void drawSideBar(QPainter *p, QPoint point);
    QList<QPoint> getBlockPoints();
    void move(QPoint direciton); //True on suscessmove, false on failed move
    QColor getColor();
    //Returns how many blocks are left
    int removeAnyBlockPointsOnRow(int row);
    void dropOneBlockIfAnyBlockIsAboveRow(int row);

    virtual void rotate();
    //Get where would be if rotated?
    virtual QList<QPoint> getPointsIfWereToRotate();

    bool isAnyPartOfBlockOverThisValue(int value);

    void setPosition(QPoint pos);
    QPoint getPosition();


protected:
    QList<QPoint> m_blockPoints;
    QPoint m_position; //The X's in the reference image "TetrisPieces.png"
    char m_rotation; // 0, 1, 2, 3 rotations. See TetrisPieces.png
    QColor m_color;
};

//I, O, T, S, Z, J, and L
class BlockI : public Block
{
public:
    BlockI(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockO : public Block
{
public:
    BlockO(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockT : public Block
{
public:
    BlockT(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockS : public Block
{
public:
    BlockS(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockZ : public Block
{
public:
    BlockZ(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockJ : public Block
{
public:
    BlockJ(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockL : public Block
{
public:
    BlockL(QPoint position);

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

class BlockNull : public Block
{
public:
    BlockNull();

    void rotate();
    QList<QPoint> getPointsIfWereToRotate();
};

#endif // BLOCK_H

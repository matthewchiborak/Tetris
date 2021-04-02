#include "block.h"

#include <QDebug>

Block::Block()
{

}

void Block::draw(QPainter *p)
{
    QBrush brush;

    brush = QBrush(getColor());

    foreach(QPoint focusPoint, getBlockPoints())
    {
        p->fillRect((focusPoint.x()*10) + 1, (focusPoint.y()*10) + 1, 8, 8, brush);
    }
}

void Block::drawSideBar(QPainter *p, QPoint point)
{
    QBrush brush;

    brush = QBrush(getColor());

    foreach(QPoint focusPoint, getBlockPoints())
    {
        //p->fillRect((focusPoint.x()*10) + 1, (focusPoint.y()*10) + 1, 8, 8, brush);
        p->fillRect(point.x() + ((focusPoint.x() - m_position.x())*10) + 1,
                    point.y() + ((focusPoint.y() - m_position.y())*10) + 1, 8, 8, brush);
    }
}

QList<QPoint> Block::getBlockPoints()
{
    return m_blockPoints;
}

void Block::move(QPoint direciton)
{
    m_position.setX(m_position.x() + direciton.x());
    m_position.setY(m_position.y() + direciton.y());

    for(int i = 0; i < m_blockPoints.length(); i++)
    {
        m_blockPoints.replace(i,
                              QPoint(m_blockPoints.at(i).x() + direciton.x(),
                                     m_blockPoints.at(i).y() + direciton.y()));
    }
}

QColor Block::getColor()
{
    return m_color;
}

int Block::removeAnyBlockPointsOnRow(int row)
{
    for(int i = 0; i < m_blockPoints.length(); i++)
    {
        if(m_blockPoints.at(i).y() == row)
        {
            m_blockPoints.removeAt(i);
            i--;
        }
    }

    return m_blockPoints.length();
}

void Block::dropOneBlockIfAnyBlockIsAboveRow(int row)
{
    for(int i = 0; i < m_blockPoints.length(); i++)
    {
        if(m_blockPoints.at(i).y() > row)
        {
            QPoint newPoint(m_blockPoints.at(i).x(), m_blockPoints.at(i).y() - 1);
            m_blockPoints.replace(i, newPoint);
        }
    }
}

void Block::rotate()
{

}

QList<QPoint> Block::getPointsIfWereToRotate()
{
    QList<QPoint> nullPoints;
    return nullPoints;
}

bool Block::isAnyPartOfBlockOverThisValue(int value)
{
    foreach(QPoint focusPoint, m_blockPoints)
    {
        if(focusPoint.y() >= value)
        {
            return true;
        }
    }

    return false;
}

void Block::setPosition(QPoint pos)
{
    QPoint moveDir(
                pos.x() - m_position.x(),
                pos.y() - m_position.y()
                );

    move(moveDir);
}

QPoint Block::getPosition()
{
    return m_position;
}


BlockI::BlockI(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::blue);

    m_blockPoints.push_back(m_position);
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 3, m_position.y()));
}

void BlockI::rotate()
{
    m_rotation = (m_rotation+1)%4;

    if(0 == m_rotation || 2 == m_rotation)
    {
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x() + 2, m_position.y()));
        m_blockPoints.replace(3, QPoint(m_position.x() + 3, m_position.y()));
    }
    else
    {
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x(), m_position.y() - 2));
        m_blockPoints.replace(3, QPoint(m_position.x(), m_position.y() - 3));
    }
}

QList<QPoint> BlockI::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    int nextRot = (m_rotation+1)%4;

    if(0 == nextRot || 2 == nextRot)
    {
        points.push_back(m_position);
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 2, m_position.y()));
        points.push_back(QPoint(m_position.x() + 3, m_position.y()));
    }
    else
    {
        points.push_back(m_position);
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x(), m_position.y() - 2));
        points.push_back(QPoint(m_position.x(), m_position.y() - 3));
    }

    return points;
}

BlockO::BlockO(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::yellow);

    m_blockPoints.push_back(m_position);
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y() - 1));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
}

void BlockO::rotate()
{
    //Dont bother. I mean. We could increate the count. But it dosent do anything
    m_rotation = (m_rotation+1)%4;
}

QList<QPoint> BlockO::getPointsIfWereToRotate()
{
    QList<QPoint> points;

    for(int i = 0; i < getBlockPoints().length(); i++)
    {
        points.push_back(getBlockPoints().at(i));
    }

    return points;
}

BlockT::BlockT(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::white);

    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
}

void BlockT::rotate()
{
    m_rotation = (m_rotation+1)%4;

    if(0 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x() + 2, m_position.y()));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 1));
    }
    else if(1 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 2));
    }
    else if(2 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x(), m_position.y() - 2));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 1));
    }
}

QList<QPoint> BlockT::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    int nextRot = (m_rotation+1)%4;

    if(0 == nextRot)
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 2, m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
    }
    else if(1 == nextRot)
    {
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 2));
    }
    else if(2 == nextRot)
    {
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x(), m_position.y() - 2));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
    }

    return points;
}

BlockS::BlockS(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::green);

    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y() - 1));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
}

void BlockS::rotate()
{
    m_rotation = (m_rotation+1)%4;

    if(0 == m_rotation || 2 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 2, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 1));
    }
    else
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 2));
    }
}

QList<QPoint> BlockS::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    int nextRot = (m_rotation+1)%4;

    if(0 == nextRot || 2 == nextRot)
    {
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 2, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
    }
    else
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 2));
    }

    return points;
}

BlockZ::BlockZ(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::lightGray);

    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
}

void BlockZ::rotate()
{
    m_rotation = (m_rotation+1)%4;

    if(0 == m_rotation || 2 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        m_blockPoints.replace(0, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x(), m_position.y() - 2));
    }
}

QList<QPoint> BlockZ::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    int nextRot = (m_rotation+1)%4;

    if(0 == nextRot || 2 == nextRot)
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x(), m_position.y() - 2));
    }

    return points;
}

BlockJ::BlockJ(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::darkBlue);

    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
}

void BlockJ::rotate()
{
    m_rotation = (m_rotation+1)%4;

    if(0 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x() + 2, m_position.y()));
        m_blockPoints.replace(3, QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else if(1 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 2));
        m_blockPoints.replace(3, QPoint(m_position.x(), m_position.y() - 2));
    }
    else if(2 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x(), m_position.y() - 2));
    }
}

QList<QPoint> BlockJ::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    int nextRot = (m_rotation+1)%4;

    if(0 == nextRot)
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 2, m_position.y()));
        points.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else if(1 == nextRot)
    {
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 2));
        points.push_back(QPoint(m_position.x(), m_position.y() - 2));
    }
    else if(2 == nextRot)
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x(), m_position.y() - 2));
    }

    return points;
}

BlockL::BlockL(QPoint position)
{
    m_position = position;
    m_rotation = 0;
    m_color = QColor(Qt::darkMagenta);

    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 1, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x() + 2, m_position.y()));
    m_blockPoints.push_back(QPoint(m_position.x(), m_position.y() - 1));
}

void BlockL::rotate()
{
    m_rotation = (m_rotation+1)%4;

    if(0 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x() + 2, m_position.y()));
        m_blockPoints.replace(3, QPoint(m_position.x(), m_position.y() - 1));
    }
    else if(1 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y()));
        m_blockPoints.replace(2, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 2));
    }
    else if(2 == m_rotation)
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(1, QPoint(m_position.x() + 1, m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x() + 2, m_position.y() - 1));
        m_blockPoints.replace(3, QPoint(m_position.x() + 2, m_position.y()));
    }
    else
    {
        m_blockPoints.replace(0, QPoint(m_position.x(), m_position.y()));
        m_blockPoints.replace(1, QPoint(m_position.x(), m_position.y() - 1));
        m_blockPoints.replace(2, QPoint(m_position.x(), m_position.y() - 2));
        m_blockPoints.replace(3, QPoint(m_position.x() + 1, m_position.y() - 2));
    }
}

QList<QPoint> BlockL::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    int nextRot = (m_rotation+1)%4;

    if(0 == nextRot)
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 2, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
    }
    else if(1 == nextRot)
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y()));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 2));
    }
    else if(2 == nextRot)
    {
        points.push_back(QPoint(m_position.x() + 2, m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 1));
        points.push_back(QPoint(m_position.x() + 2, m_position.y() - 1));
    }
    else
    {
        points.push_back(QPoint(m_position.x(), m_position.y()));
        points.push_back(QPoint(m_position.x(), m_position.y() - 1));
        points.push_back(QPoint(m_position.x(), m_position.y() - 2));
        points.push_back(QPoint(m_position.x() + 1, m_position.y() - 2));
    }

    return points;
}

BlockNull::BlockNull()
{

}

void BlockNull::rotate()
{

}

QList<QPoint> BlockNull::getPointsIfWereToRotate()
{
    QList<QPoint> points;
    return points;
}

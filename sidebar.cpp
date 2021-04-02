#include "sidebar.h"

#include "boardmodel.h"
#include <QStaticText>
#include "block.h"

SideBar::SideBar()
{

}

void SideBar::draw(QPainter *p, BoardModel *model, QTransform textTransform)
{
    QBrush brush(Qt::gray);

    p->fillRect(100, 0, 50, 200, brush);

    p->setPen(QPen(Qt::white));
    p->setTransform(textTransform, false);

    QStaticText st("Line Clears: " + QString::number(model->getNumberOfLineClears()));
    QStaticText next("Next: ");
    QStaticText hold("Hold: ");

    p->drawStaticText(100, -200, st);

    p->drawStaticText(100, -100, next);
    if(model->getNextBlock() != nullptr)
        model->getNextBlock()->drawSideBar(p, QPoint(150,-100));

    p->drawStaticText(100, 0, hold);
    if(model->getNextBlock() != nullptr)
        model->getHoldBlock()->drawSideBar(p, QPoint(150,0));
}

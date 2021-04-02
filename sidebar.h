#ifndef SIDEBAR_H
#define SIDEBAR_H

//Serves as the view to display current gameplay information

#include <QPainter>

class BoardModel;

class SideBar
{
public:
    SideBar();

    void draw(QPainter *p, BoardModel * model, QTransform textTransform);
};

#endif // SIDEBAR_H

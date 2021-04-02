#include "inputcommandfactory.h"

#include "inputcommand.h"

InputCommandFactory::InputCommandFactory()
{

}

InputCommand *InputCommandFactory::getCommand(QKeyEvent *e)
{
    return nullptr;
}

InputCommandPlayingFactory::InputCommandPlayingFactory()
{

}

InputCommand *InputCommandPlayingFactory::getCommand(QKeyEvent *e)
{
    if(e->key() == Qt::Key_A)
    {
        QPoint dir(-1,0);
        return new InputBlockMoveCommand(dir);
    }
    if(e->key() == Qt::Key_D)
    {
        QPoint dir(1,0);
        return new InputBlockMoveCommand(dir);
    }
    if(e->key() == Qt::Key_S)
    {
        return new InputBlockDropCommand();
    }
    if(e->key() == Qt::Key_E)
    {
        return new InputBlockRotateCommand();
    }
    if(e->key() == Qt::Key_R)
    {
        return new InputBlockHoldCommand();
    }

    //Do nothing
    QPoint dir(0,0);
    return new InputBlockMoveCommand(dir);
}

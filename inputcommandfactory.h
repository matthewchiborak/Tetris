#ifndef INPUTCOMMANDFACTORY_H
#define INPUTCOMMANDFACTORY_H

#include <QQueue>
#include <QKeyEvent>

class InputCommand;

class InputCommandFactory
{
public:
    InputCommandFactory();

    virtual InputCommand * getCommand(QKeyEvent * e);
};

class InputCommandPlayingFactory : public InputCommandFactory
{
public:
    InputCommandPlayingFactory();

    InputCommand *getCommand(QKeyEvent * e);
};

#endif // INPUTCOMMANDFACTORY_H

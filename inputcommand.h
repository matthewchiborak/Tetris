#ifndef INPUTCOMMAND_H
#define INPUTCOMMAND_H

#include <QPoint>

class Block;
class BoardModel;

class InputCommand
{
public:
    InputCommand();

    virtual void execute(BoardModel * modelToCommand);
};

class InputBlockMoveCommand : public InputCommand
{
public:
    InputBlockMoveCommand(QPoint dir);

    void execute(BoardModel * modelToCommand);

private:
    QPoint m_dir;
};

class InputBlockDropCommand : public InputCommand
{
public:
    InputBlockDropCommand();

    void execute(BoardModel * modelToCommand);
};

class InputBlockRotateCommand : public InputCommand
{
public:
    InputBlockRotateCommand();

    void execute(BoardModel * modelToCommand);
};

class InputBlockHoldCommand : public InputCommand
{
public:
    InputBlockHoldCommand();

    void execute(BoardModel * modelToCommand);
};

#endif // INPUTCOMMAND_H

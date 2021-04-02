#include "inputcommand.h"

#include "boardmodel.h"

InputCommand::InputCommand()
{

}

void InputCommand::execute(BoardModel *modelToCommand)
{

}

InputBlockMoveCommand::InputBlockMoveCommand(QPoint dir)
    : m_dir(dir)
{

}

void InputBlockMoveCommand::execute(BoardModel * modelToCommand)
{
    modelToCommand->moveCurrentBlock(m_dir);
}

InputBlockDropCommand::InputBlockDropCommand()
{

}

void InputBlockDropCommand::execute(BoardModel *modelToCommand)
{
    modelToCommand->dropCurrentBlock();
}

InputBlockRotateCommand::InputBlockRotateCommand()
{

}

void InputBlockRotateCommand::execute(BoardModel *modelToCommand)
{
    modelToCommand->rotateCurrentBlock();
}

InputBlockHoldCommand::InputBlockHoldCommand()
{

}

void InputBlockHoldCommand::execute(BoardModel *modelToCommand)
{
    modelToCommand->holdBlock();
}

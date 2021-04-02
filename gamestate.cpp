#include "gamestate.h"

#include "blockrandomfactory.h"

#include "boardmodel.h"
#include "inputcommand.h"
#include "block.h"

#include <QPoint>
#include <QQueue>

GameState::GameState()
{
    m_secondLastTimeHandled = QTime::currentTime();
    m_lastTimeHandled = m_secondLastTimeHandled;
}

GameState *GameState::handle(BoardModel *model, QQueue<InputCommand*> * inputQueue)
{
    m_secondLastTimeHandled = m_lastTimeHandled;
    m_lastTimeHandled = QTime::currentTime();

    //If no changes, the gamestate will be the same
    m_nextGameState = this;
    m_modelReference = model;
    m_inputQueueRef = inputQueue;

    userInputUpdate();
    applyGravityUpdate();
    checkIfPieceIsDoneUpdate();
    checkIfGameOverUpdate();
    finalUpdate();

    return m_nextGameState;
}

int GameState::deltaTime()
{
    return m_secondLastTimeHandled.msecsTo(m_lastTimeHandled);
}

void GameState::userInputUpdate()
{

}

void GameState::applyGravityUpdate()
{

}

void GameState::checkIfPieceIsDoneUpdate()
{

}

void GameState::checkIfGameOverUpdate()
{

}

void GameState::finalUpdate()
{

}


PlayingGameState::PlayingGameState()
{
    m_lastTimeAppliedGravity = 0;
}

void PlayingGameState::userInputUpdate()
{
    while(!m_inputQueueRef->isEmpty())
    {
        m_inputQueueRef->dequeue()->execute(m_modelReference);
    }
}

void PlayingGameState::applyGravityUpdate()
{
    m_lastTimeAppliedGravity += deltaTime();

    m_gravityWasApplied = true;

    if(m_lastTimeAppliedGravity > m_modelReference->getGravity())
    {
        m_lastTimeAppliedGravity = 0;

        QPoint dir(0, -1);

        m_gravityWasApplied = m_modelReference->moveCurrentBlock(dir);
    }
}

void PlayingGameState::checkIfPieceIsDoneUpdate()
{
    //If the current piece has stopped moving due to gravity. if it has, piece is done
    if(!m_gravityWasApplied)
    {
        m_modelReference->setCurrentBlockInPlace();
        m_modelReference->checkAndCleanUpLines();
        m_nextGameState = new CreatingPieceGameState();
    }
    //Check if the current piece is a null object.
    else if(m_modelReference->checkAndDeleteCurrentBlockIfNull())
    {
        m_modelReference->setIgnoreGameOverCheck(true);
        m_nextGameState = new CreatingPieceGameState();
    }
}

void PlayingGameState::checkIfGameOverUpdate()
{

}

void PlayingGameState::finalUpdate()
{

}

CreatingPieceGameState::CreatingPieceGameState()
{

}

void CreatingPieceGameState::userInputUpdate()
{
    //User has no control over what piece they get
}

void CreatingPieceGameState::applyGravityUpdate()
{
    //Piece not created yet dont gravity it yet
     m_modelReference->setGravityBasedOnLineClears();
}

void CreatingPieceGameState::checkIfPieceIsDoneUpdate()
{

}

void CreatingPieceGameState::checkIfGameOverUpdate()
{
    m_actuallyDontMakeThePiece = false;

    //If its actually a game over, dont make the next piece
    if(!m_modelReference->getIgnoreGameOverCheck())
    {
        if(m_modelReference->getCurrentBlock()->isAnyPartOfBlockOverThisValue(20))
        {
            m_nextGameState = new GameOverGameState();
            m_actuallyDontMakeThePiece = true;
        }
    }
}

void CreatingPieceGameState::finalUpdate()
{
    if(!m_actuallyDontMakeThePiece)
    {
        //Create the new piece to be controlelr by the player
        BlockRandomFactory factory;

        Block * newBlock = factory.getBlock();

        m_modelReference->addNewPieceForTheBoardForPlayerToUse(newBlock);

        //Update the state
        m_modelReference->setIgnoreGameOverCheck(false);
        m_nextGameState = new PlayingGameState();
    }
}

GameStartGameState::GameStartGameState()
{

}

void GameStartGameState::userInputUpdate()
{

}

void GameStartGameState::applyGravityUpdate()
{

}

void GameStartGameState::checkIfPieceIsDoneUpdate()
{

}

void GameStartGameState::checkIfGameOverUpdate()
{

}

void GameStartGameState::finalUpdate()
{
    //Create the new piece to be controlelr by the player
    BlockRandomFactory factory;

    Block * newBlock = factory.getBlock();
    Block * nextBlock = factory.getBlock();

    m_modelReference->initPieces(newBlock, nextBlock);

    //Update the state
    m_nextGameState = new PlayingGameState();
}

GameOverGameState::GameOverGameState()
{

}

void GameOverGameState::userInputUpdate()
{

}

void GameOverGameState::applyGravityUpdate()
{

}

void GameOverGameState::checkIfPieceIsDoneUpdate()
{

}

void GameOverGameState::checkIfGameOverUpdate()
{

}

void GameOverGameState::finalUpdate()
{
    qDebug() << "The Game Is Over";
}

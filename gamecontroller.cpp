#include "gamecontroller.h"

#include "boardmodel.h"

GameController::GameController(OpenGLWindow *view, QQueue<InputCommand *> *inputQueue, BoardModel *boardModel)
    : m_view(view)
    , m_inputQueue(inputQueue)
    , m_currentGameState(new GameStartGameState())
    , m_boardModel(boardModel)
{
    //Inject all the dependancies

    //Connect the signal and slots
    //connect(m_view, SIGNAL(detectedInputSignal()), this, SLOT(detectedInputSlot()));

    connect(&m_refreshTimer, SIGNAL(timeout()), SLOT(refreshTimeoutSlot()));
    m_refreshTimer.start(100); // Set interval to whatever you want
}

void GameController::refreshTimeoutSlot()
{
    if(m_boardModel->getMutex()->tryLock(1000))
    {
        //Based on the current state, the game will update accordingly
        m_currentGameState = m_currentGameState->handle(m_boardModel, m_inputQueue);

        m_boardModel->getMutex()->unlock();
    }
}

//void GameController::detectedInputSlot()
//{
//    //Need an iterator to iterate through the queue. Well its just a queue. I'll use iterator else where
//    while(!m_inputQueue->isEmpty())
//    {
//        //based on the current state of the game, the input will be handled differently
//    }
//}

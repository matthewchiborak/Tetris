#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "openglwindow.h"
#include <gamestate.h>

#include <QTimer>

class BoardModel;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(OpenGLWindow * view, QQueue<InputCommand*> * inputQueue, BoardModel * boardModel);

public slots:
    //Called when something is added to the input queue
    //void detectedInputSlot();
    void refreshTimeoutSlot();

private:
    OpenGLWindow * m_view;
    QQueue<InputCommand*> * m_inputQueue;

    //Timer to use to continually to update the gamestate
    QTimer m_refreshTimer;
    GameState * m_currentGameState;
    BoardModel * m_boardModel;
};

#endif // GAMECONTROLLER_H

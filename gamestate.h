#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QKeyEvent>
#include <QDebug>
#include <QTime>

class BoardModel;
class InputCommand;

class GameState
{
public:
    //Will need to pass a refernece to the model
    GameState();

    //Pass in the boardmodel and will update the model accordeingly
    GameState * handle(BoardModel * model, QQueue<InputCommand*> * inputQueue);

    int deltaTime();

protected:
    GameState * m_nextGameState;

    BoardModel * m_modelReference;
    QQueue<InputCommand*> * m_inputQueueRef;

    QTime m_lastTimeHandled;
    QTime m_secondLastTimeHandled;

    bool m_gravityWasApplied;

    virtual void userInputUpdate(); //Game updates based on user input
    virtual void applyGravityUpdate(); //Game updates based on gravity
    virtual void checkIfPieceIsDoneUpdate(); //Tetris piece is now locked in place
    virtual void checkIfGameOverUpdate(); //Check if the top of the screen has been hit
    virtual void finalUpdate(); //Do any updates that will be done last
};

class PlayingGameState : public GameState
{
public:
    PlayingGameState();

private:
    void userInputUpdate(); //Game updates based on user input
    void applyGravityUpdate(); //Game updates based on gravity
    void checkIfPieceIsDoneUpdate(); //Tetris piece is now locked in place
    void checkIfGameOverUpdate(); //Check if the top of the screen has been hit
    void finalUpdate();

    int m_lastTimeAppliedGravity;
};

class CreatingPieceGameState : public GameState
{
public:
    CreatingPieceGameState();

private:
    void userInputUpdate(); //Game updates based on user input
    void applyGravityUpdate(); //Game updates based on gravity
    void checkIfPieceIsDoneUpdate(); //Tetris piece is now locked in place
    void checkIfGameOverUpdate(); //Check if the top of the screen has been hit
    void finalUpdate();

    bool m_actuallyDontMakeThePiece;
};

class GameStartGameState : public GameState
{
public:
    GameStartGameState();

private:
    void userInputUpdate(); //Game updates based on user input
    void applyGravityUpdate(); //Game updates based on gravity
    void checkIfPieceIsDoneUpdate(); //Tetris piece is now locked in place
    void checkIfGameOverUpdate(); //Check if the top of the screen has been hit
    void finalUpdate();
};

class GameOverGameState : public GameState
{
public:
    GameOverGameState();

private:
    void userInputUpdate(); //Game updates based on user input
    void applyGravityUpdate(); //Game updates based on gravity
    void checkIfPieceIsDoneUpdate(); //Tetris piece is now locked in place
    void checkIfGameOverUpdate(); //Check if the top of the screen has been hit
    void finalUpdate();
};

#endif // GAMESTATE_H

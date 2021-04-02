#include "mainwindow.h"

#include <QApplication>
#include <QQueue>
#include <QKeyEvent>
#include <QMutex>

#include "openglwindow.h"
#include "gamecontroller.h"
#include "boardmodel.h"
#include "inputcommand.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //The input queue for handling all the inputs
    QQueue<InputCommand*> inputQueue;

    QMutex modelMutex;

    //Model for storing the game information related to the board
    BoardModel boardModel;

    //TODO remove this from main and put into a game "scene"
    //The game view. Will have to inject into the game controller
    OpenGLWindow window(&inputQueue, &boardModel);
    window.resize(450, 600);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    window.setFormat(fmt);
    window.show();

    GameController gameController(&window, &inputQueue, &boardModel);

    return app.exec();
}

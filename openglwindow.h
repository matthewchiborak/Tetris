#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWindow>
#include <QScreen>
#include <QPainter>
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QStaticText>
#include <QKeyEvent>
#include <QPainterPath>
#include <QQueue>
#include <QDebug>

#include "background_renderer.h"
#include "sidebar.h"

class BoardModel;
class InputCommand;
class InputCommandPlayingFactory;

//This is the game view now because I realize it was redunand to both classes


static QPainterPath painterPathForTriangle()
{
    static const QPointF bottomLeft(-1.0, -1.0);
    static const QPointF top(0.0, 1.0);
    static const QPointF bottomRight(1.0, -1.0);

    QPainterPath path(bottomLeft);
    path.lineTo(top);
    path.lineTo(bottomRight);
    path.closeSubpath();
    return path;

}

class OpenGLWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    OpenGLWindow(QQueue<InputCommand*> * inputQueue, BoardModel * boardModel);

//signals:
//    void detectedInputSignal();

protected:
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;

private:
    void setAnimating(bool enabled);

    QMatrix4x4 m_window_normalised_matrix;
    QMatrix4x4 m_window_painter_matrix;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model_triangle;
    QMatrix4x4 m_model_text;
    QBrush m_brush;

    FragmentToy m_fragment_toy;
    QStaticText m_text_layout;
    bool m_animate;

    //Queue for putting the inputs to be handled by the controller
    QQueue<InputCommand*> * m_inputQueue;
    BoardModel * m_boardModel;
    SideBar m_sideBar;

    InputCommandPlayingFactory * m_inputCommandFactory;
};

#endif // OPENGLWINDOW_H

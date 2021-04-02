#include "openglwindow.h"

#include "boardmodel.h"

#include "inputcommand.h"
#include "inputcommandfactory.h"

OpenGLWindow::OpenGLWindow(QQueue<InputCommand *> *inputQueue, BoardModel * boardModel)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate)
    , m_fragment_toy("background.frag")
    , m_text_layout("The triangle and this text is rendered with QPainter")
    , m_animate(true)
    , m_inputQueue(inputQueue)
    , m_boardModel(boardModel)
    , m_inputCommandFactory(new InputCommandPlayingFactory())

{
    m_view.lookAt(QVector3D(0,0,0),
                  QVector3D(0,0,0),
                  QVector3D(0,1,0));

    QLinearGradient gradient(QPointF(-1,-1), QPointF(1,1));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);

    m_brush = QBrush(Qt::black);

    setAnimating(m_animate);

}

void OpenGLWindow::paintGL()
{
    if(m_boardModel->getMutex()->tryLock(1000))
    {
        //Need a rendering strategy/state. Could be title screen, pause
        //screen etc. Would be related to game state. hmm.
        //Could be a list of strategies to render.
        //Game board view. Pause on top of it. Scoreboard. Perfect.
        //Based on gamestate changes?????

        QPainter p(this);
        p.setWorldTransform(m_window_normalised_matrix.toTransform());

        QMatrix4x4 mvp = m_projection * m_view;// * m_model_triangle;
        p.setTransform(mvp.toTransform(), true);

        //Clear the screen
        p.fillRect(0, 0, 150, 200, m_brush);

        m_boardModel->draw(&p);

        //Draw the sidebar
        QTransform text_transform = (m_window_painter_matrix * m_view * m_model_text).toTransform();
        m_sideBar.draw(&p, m_boardModel, text_transform);

    //    m_fragment_toy.draw(size());

    //    QPainter p(this);
    //    p.setWorldTransform(m_window_normalised_matrix.toTransform());

    //    QMatrix4x4 mvp = m_projection * m_view * m_model_triangle;
    //    p.setTransform(mvp.toTransform(), true);

    //    p.fillPath(painterPathForTriangle(), m_brush);

    //    QTransform text_transform = (m_window_painter_matrix * m_view * m_model_text).toTransform();
    //    p.setTransform(text_transform, false);
    //    p.setPen(QPen(Qt::white));
    //    m_text_layout.prepare(text_transform);
    //    qreal x = - (m_text_layout.size().width() / 2);
    //    qreal y = 0;
    //    p.drawStaticText(x, y, m_text_layout);

    //    m_model_triangle.rotate(-1, 0, 1, 0);
    //    m_model_text.rotate(1, 0, 1, 0);

        m_boardModel->getMutex()->unlock();
    }

}

void OpenGLWindow::resizeGL(int w, int h)
{
    m_window_normalised_matrix.setToIdentity();
    m_window_normalised_matrix.translate(w / 2.0, h / 2.0);
    m_window_normalised_matrix.scale(w / 2.0, -h / 2.0);

    m_window_painter_matrix.setToIdentity();
    m_window_painter_matrix.translate(w / 2.0, h / 2.0);

    m_text_layout.setTextWidth(std::max(w * 0.2, 80.0));

    m_projection.setToIdentity();
    m_projection.ortho(0.0f, 150.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 100.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.perspective(45.f, qreal(w) / qreal(h), 0.1f, 100.f);

}

void OpenGLWindow::keyPressEvent(QKeyEvent *e)
{
    //Will input into the input queue and notify the gamecontroller
    m_inputQueue->enqueue(m_inputCommandFactory->getCommand(e));

    //emit detectedInputSignal();

//    if (e->key() == Qt::Key_P) { // pause
//        m_animate = !m_animate;
//        setAnimating(m_animate);
//    }
}

void OpenGLWindow::setAnimating(bool enabled)
{
    if (enabled) {
        // Animate continuously, throttled by the blocking swapBuffers() call the
        // QOpenGLWindow internally executes after each paint. Once that is done
        // (frameSwapped signal is emitted), we schedule a new update. This
        // obviously assumes that the swap interval (see
        // QSurfaceFormat::setSwapInterval()) is non-zero.
        connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
        update();
    } else {
        disconnect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    }
}

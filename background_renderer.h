#ifndef FRAGMENT_TOY_H
#define FRAGMENT_TOY_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QFileSystemWatcher>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

//used by openglwindow right now to draw the backgorund

class FragmentToy : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    FragmentToy(const QString &fragmentSource, QObject *parent = 0);

    void draw(const QSize &windowSize);

private:
    void fileChanged(const QString &path);
    bool m_recompile_shaders;
#ifndef QT_NO_FILESYSTEMWATCHER
    QFileSystemWatcher m_watcher;
#endif
    QString m_fragment_file;
    QDateTime m_fragment_file_last_modified;

    QScopedPointer<QOpenGLShaderProgram> m_program;
    QScopedPointer<QOpenGLShader> m_vertex_shader;
    QScopedPointer<QOpenGLShader> m_fragment_shader;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vertex_buffer;
    GLuint m_vertex_coord_pos;
};

#endif //FRAGMENT_TOY_H


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <memory>

#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLBuffer)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT // enabled meta object abilities
public:
    GLWidget(const QColor &background);
    ~GLWidget();

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();

    QOpenGLVertexArrayObject m_vao;

    QOpenGLBuffer *m_ebo = nullptr;
    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLShader *m_vert_shader = nullptr;
    QOpenGLShader *m_frag_shader = nullptr;
    QOpenGLShaderProgram *m_program = nullptr;

    int m_vertex_attr;

    QColor m_background;
    QMetaObject::Connection m_contextWatchConnection;
};

#endif // GLWIDGET_H

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

    std::unique_ptr<QOpenGLBuffer> m_ebo;
    std::unique_ptr<QOpenGLBuffer> m_vbo;
    std::unique_ptr<QOpenGLShader> m_vert_shader;
    std::unique_ptr<QOpenGLShader> m_frag_shader;
    std::unique_ptr<QOpenGLShaderProgram> m_program;

    int m_vertex_attr;

    QColor m_background;
    QMetaObject::Connection m_contextWatchConnection;
};

#endif // GLWIDGET_H

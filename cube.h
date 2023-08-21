#ifndef CUBE_H
#define CUBE_H

#include <memory>

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>

QT_FORWARD_DECLARE_CLASS(QOpenGLBuffer)

class Cube
{
public:
    Cube();
    ~Cube();

    void init();
    void draw();

    void setTransform(const QMatrix4x4 &m);
    QMatrix4x4 getTransform();

private:
    QOpenGLVertexArrayObject m_vao;

    std::unique_ptr<QOpenGLBuffer> m_ebo;
    std::unique_ptr<QOpenGLBuffer> m_vbo;

    QMatrix4x4 m_transform;
};

#endif // CUBE_H

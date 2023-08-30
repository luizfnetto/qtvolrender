#ifndef FBOQUAD_H
#define FBOQUAD_H

#include <memory>

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>

QT_FORWARD_DECLARE_CLASS(QOpenGLBuffer)

class FboQuad
{
public:
    FboQuad();
    ~FboQuad();

    void init();
    void draw();

    void setTransform(const QMatrix4x4 &m);
    QMatrix4x4 getTransform();

private:
    QOpenGLVertexArrayObject m_vao;

    std::unique_ptr<QOpenGLBuffer> m_vbo;

    QMatrix4x4 m_transform;
};

#endif // QUAD_H

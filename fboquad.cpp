#include "fboquad.h"

#include <QOpenGLBuffer>

using namespace std;

FboQuad::FboQuad()
{

}

FboQuad::~FboQuad()
{

}

void FboQuad::init()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    GLfloat vertices[] = {
        -1.f, -1.f, 0.f,
        1.0f, -1.f, 0.f,
        -1.f, 1.0f, 0.f,
        1.0f, 1.0f, 0.f
    };

    m_vao.create();
    m_vao.bind();

    m_vbo = make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_vbo->release();
    m_vao.release();
}

void FboQuad::draw()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    m_vao.bind();
    f->glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
    m_vao.release();
}

void FboQuad::setTransform(const QMatrix4x4 &m)
{
    m_transform = m;
}

QMatrix4x4 FboQuad::getTransform()
{
    return m_transform;
}

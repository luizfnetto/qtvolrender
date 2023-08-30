#include "cube.h"

#include <QOpenGLBuffer>

using namespace std;

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::init()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    GLfloat vertices[] = {
        -.5f, -.5f, 0.5f,
        0.5f, -.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -.5f, 0.5f, 0.5f,
        -.5f, -.5f, -.5f,
        0.5f, -.5f, -.5f,
        0.5f, 0.5f, -.5f,
        -.5f, 0.5f, -.5f
    };

    GLuint indices[] {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        3, 2, 6,
        6, 7, 3,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // left
        4, 0, 3,
        3, 7, 4,
        // right
        1, 5, 6,
        6, 2, 1,
    };

    m_vao.create();
    m_vao.bind();

    m_ebo = make_unique<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer);
    m_ebo->create();
    m_ebo->bind();
    m_ebo->allocate(indices, sizeof(indices));

    m_vbo = make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_vbo->release();
    m_vao.release();
}

void Cube::draw()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    m_vao.bind();
    f->glDrawElements (GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
    m_vao.release();
}

void Cube::setTransform(const QMatrix4x4 &m)
{
    m_transform = m;
}

QMatrix4x4 Cube::getTransform()
{
    return m_transform;
}

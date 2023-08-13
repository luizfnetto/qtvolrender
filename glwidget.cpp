#include "glwidget.h"

GLWidget::GLWidget(const QColor &background)
    : m_background(background)
{
}

GLWidget::~GLWidget()
{
    reset();
}

void GLWidget::reset()
{
    // Release all OpenGL resources.
    makeCurrent();
    doneCurrent();

    QObject::disconnect(m_contextWatchConnection);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void GLWidget::paintGL()
{
    glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update();
}

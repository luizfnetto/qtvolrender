#include "glwidget.h"

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QDir>

using namespace std;

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
    Q_INIT_RESOURCE(resources);

    initializeOpenGLFunctions();

    glFrontFace (GL_CCW);
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glEnable (GL_DEPTH_TEST);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
//    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

    m_contextWatchConnection = QObject::connect(context(), &QOpenGLContext::aboutToBeDestroyed, context(), [this] { reset(); });
}

void GLWidget::paintGL()
{
    glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_volume_render) {
        m_volume_render = make_unique<VolumeRender>();
        m_volume_render->init();
    }

    m_volume_render->render();

    update();
}



#include "glwidget.h"

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

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

static const char *vertexShaderSource =
    "layout (location = 0) in vec3 vertex;\n"
    "void main() {\n"
    "    gl_Position = vec4(vertex, 1.0);\n"
    "}\n";

static const char *fragmentShaderSource =
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n"
    "}\n";

QByteArray versionedShaderCode(const char *src)
{
    QByteArray versionedSrc;

    if (QOpenGLContext::currentContext()->isOpenGLES())
        versionedSrc.append(QByteArrayLiteral("#version 300 es\n"));
    else
        versionedSrc.append(QByteArrayLiteral("#version 330\n"));

    versionedSrc.append(src);
    return versionedSrc;
}

void GLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    m_vert_shader = make_unique<QOpenGLShader>(QOpenGLShader::Vertex);
    m_vert_shader->compileSourceCode(versionedShaderCode(vertexShaderSource));

    m_frag_shader = make_unique<QOpenGLShader>(QOpenGLShader::Fragment);
    m_frag_shader->compileSourceCode(versionedShaderCode(fragmentShaderSource));

    m_program = make_unique<QOpenGLShaderProgram>(this);
    m_program->addShader(m_vert_shader.get());
    m_program->addShader(m_frag_shader.get());
    m_program->link();

    m_cube.init();

    f->glFrontFace(GL_CW);
    f->glCullFace(GL_FRONT);
    f->glEnable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);

    m_contextWatchConnection = QObject::connect(context(), &QOpenGLContext::aboutToBeDestroyed, context(), [this] { reset(); });
}

void GLWidget::paintGL()
{
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    m_cube.draw();

    update();
}

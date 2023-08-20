#include "glwidget.h"

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

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

    m_vert_shader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_vert_shader->compileSourceCode(versionedShaderCode(vertexShaderSource));

    m_frag_shader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_frag_shader->compileSourceCode(versionedShaderCode(fragmentShaderSource));

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShader(m_vert_shader);
    m_program->addShader(m_frag_shader);
    m_program->link();

    m_vertex_attr = m_program->attributeLocation("vertex");

    float vertices[] = {
        0.0f, 0.5f, 0.0f, // Top
        -.5f, -.5f, 0.0f, // Botton left
        0.5f, -.5f, 0.0f  // Botton right
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    m_vao.create();
    m_vao.bind();


    m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ebo->create();
    m_ebo->bind();
    m_ebo->allocate(indices, sizeof(indices));

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_vbo->release();
    m_vao.release();

    m_contextWatchConnection = QObject::connect(context(), &QOpenGLContext::aboutToBeDestroyed, context(), [this] { reset(); });

    f->glFrontFace(GL_CW);
    f->glCullFace(GL_FRONT);
    f->glEnable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    m_vao.bind();
    f->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//    f->glDrawArrays(GL_TRIANGLES, 0, 3);
    update();
}

#include "volumerender.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLShaderProgram>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>

#include "volumedata.h"

using namespace std;

VolumeRender::VolumeRender()
{

}

VolumeRender::~VolumeRender()
{
    glDeleteTextures(1, &m_volume_tex_id);
}

void VolumeRender::init()
{
    GLint vp [4];
    glGetIntegerv (GL_VIEWPORT, vp);

    m_width = static_cast<int>(vp[2] - vp[0]);
    m_height = static_cast<int>(vp[3] - vp[1]);

    m_camera = make_unique<Camera>(m_width, m_height);

    qDebug() << "void VolumeRender::init()\nPWD:" << QDir::currentPath();
    qDebug() << "VP: " << vp[0] << " " << vp[1] << " " << vp[2] << " " << vp[3];

    m_pre_pass_program = make_unique<QOpenGLShaderProgram>();
    m_pre_pass_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":shaders/pre_pass.vert");
    m_pre_pass_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":shaders/pre_pass.frag");
    m_pre_pass_program->link();

    m_volume_pass_program = make_unique<QOpenGLShaderProgram>();
    m_volume_pass_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":shaders/volume_pass.vert");
    m_volume_pass_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":shaders/volume_pass.frag");
    m_volume_pass_program->link();

    createFBOs();

    m_fboquad.init();
    m_cube.init();


    // TODO: Temporary loading data here
    QString base_path = QStandardPaths::locate(QStandardPaths::DocumentsLocation, "qtvolrender", QStandardPaths::LocateDirectory);
//    m_volume_data = make_unique<VolumeData>(base_path + "/data/fuel.raw", 64, EVolumeDataType::UInt8);
//    m_volume_data = make_unique<VolumeData>(base_path + "/data/hydrogenAtom.raw", 128, EVolumeDataType::UInt8);
//    m_volume_data = make_unique<VolumeData>(base_path + "/data/bonsai.raw", 256, EVolumeDataType::UInt8);
//    m_volume_data = make_unique<VolumeData>(base_path + "/data/skull_256x256x256_uint8.raw", 256, EVolumeDataType::UInt8);
//    m_volume_data = make_unique<VolumeData>(base_path + "/data/bunny_512x512x361_uint16.raw", 512, 512, 361, EVolumeDataType::UInt16);

    m_volume_data = make_unique<VolumeData>(":data/foot.raw", 256, EVolumeDataType::UInt8);

    auto [dim_x, dim_y, dim_z] = m_volume_data->GetDimesionsSizes();

    glGenTextures(1, &m_volume_tex_id);
    glBindTexture (GL_TEXTURE_3D, m_volume_tex_id);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, dim_x, dim_y, dim_z, 0, GL_RED, GL_FLOAT, m_volume_data->GetNormalizedData().data());
    glTexParameteri (GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture (GL_TEXTURE_3D, 0);

}

void VolumeRender::render()
{
    if (!m_fbo_front || !m_fbo_back)
        return;

    m_camera->update();

    fboDrawVolumeFront();
    fboDrawVolumeBack();

    volumePass();
}

void VolumeRender::resize(int width, int height)
{
    if (width == m_width && height == m_height)
        return;

    m_width = width;
    m_height = height;

    qDebug() << "updateWinDim";
    qDebug() << "Params:" << width << " " << height;

    createFBOs();
    m_camera->resize(m_width, m_height);
}

void VolumeRender::createFBOs()
{
    if (m_fbo_front)
        m_fbo_front.release();

    if (m_fbo_back)
        m_fbo_back.release();

    if (m_width == 0 || m_height == 0)
        return;

    QOpenGLFramebufferObjectFormat format;
    format.setInternalTextureFormat(GL_RGBA32F);
    format.setAttachment(QOpenGLFramebufferObject::Depth);

    m_fbo_front = make_unique<QOpenGLFramebufferObject>(m_width, m_height, format);
    if (m_fbo_front->isValid())
        qDebug() << "Valid front pass FBO";
    else
        qDebug() << "ERROR: Invalid front pass FBO";

    m_fbo_back = make_unique<QOpenGLFramebufferObject>(m_width, m_height, format);
    if (m_fbo_back->isValid())
        qDebug() << "Valid back pass FBO";
    else
        qDebug() << "ERROR: Invalid front pass FBO";
}

void VolumeRender::createTextureVolume()
{
//    if (dim_x == 0 || dim_y == 0 || dim_z == 0)
//        return;

//TODO:
//    glBindTexture(GL_TEXTURE_3D, m_volume_tex_id);
//    glTexSubImage3D (GL_TEXTURE_3D, 0, 0, 0, 0, dim_x, dim_y, dim_z, GL_RED, GL_FLOAT, volume_data.data());
//    glBindTexture(GL_TEXTURE_3D, 0);
}

void VolumeRender::fboDrawVolumeFront()
{
    fboPrePass(GL_BACK);
}

void VolumeRender::fboDrawVolumeBack()
{
    fboPrePass(GL_FRONT);
}

void VolumeRender::fboPrePass(GLenum cull_facing_mode)
{
    m_pre_pass_program->bind();
    QMatrix4x4 model = m_cube.getTransform();
//    model.rotate(90, 1, 0, 0); //bunny
    QMatrix4x4 view = m_camera->getView();
    QMatrix4x4 view_projection = m_camera->getViewProjection();
    m_pre_pass_program->setUniformValue("mvp", view_projection*model);
    m_pre_pass_program->setUniformValue("modelView", view*model);

    const GLenum bufs[] = {GL_COLOR_ATTACHMENT0};
    const GLfloat clear_color[] = {0.0f, 0.0f, 0.0f, 0.0f};
    const GLfloat clear_depth[] = {1.0f, 1.0f, 1.0f, 1.0f};

    if (cull_facing_mode == GL_BACK)
        m_fbo_front->bind();
    else
        m_fbo_back->bind();

    glDrawBuffers (1, bufs);

    glClearBufferfv (GL_COLOR, 0, clear_color);
    glClearBufferfv (GL_DEPTH, 0, clear_depth);

    glEnable (GL_CULL_FACE);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    glCullFace (cull_facing_mode);

    m_cube.draw ();

    if (cull_facing_mode == GL_BACK)
        m_fbo_front->release();
    else
        m_fbo_back->release();

    m_pre_pass_program->release();
}

void VolumeRender::volumePass()
{
    m_volume_pass_program->bind();
    m_volume_pass_program->setUniformValue("winDim", (float)m_width, (float)m_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawBuffer(GL_BACK);

    glDisable (GL_DEPTH_TEST);
    glDisable (GL_CULL_FACE);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fbo_front->texture());
    m_volume_pass_program->setUniformValue("frontTex", 0);

    glActiveTexture (GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_fbo_back->texture());
    m_volume_pass_program->setUniformValue("backTex", 1);

    glActiveTexture (GL_TEXTURE2);
    glBindTexture (GL_TEXTURE_3D, m_volume_tex_id);
    m_volume_pass_program->setUniformValue("volumeTex", 2);

    m_fboquad.draw();

    m_volume_pass_program->release();

    glBindTexture (GL_TEXTURE_3D, 0);

    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_2D, 0);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, 0);
}

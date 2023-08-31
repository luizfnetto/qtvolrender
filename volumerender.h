#ifndef VOLUMERENDER_H
#define VOLUMERENDER_H

#include <vector>
#include <memory>
#include <QMatrix4x4>

#include "fboquad.h"
#include "cube.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLFramebufferObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class VolumeRender
{
public:
    VolumeRender();
    ~VolumeRender();

    void init();
    void render();
    void resize(int width, int height);

private:
    void createFBOs();
    void createTextureVolume();

    void fboDrawVolumeFront();

    void fboDrawVolumeBack();

    // cull_facing_mode can be GL_FRONT or GL_BACK
    void fboPrePass(GLenum cull_facing_mode);

    void volumePass();

    // TODO: Move volume data to its own class
    void openQtRawFile(QString path, int dim_size);

private:
    int m_width {0};
    int m_height {0};

    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelview;

    FboQuad m_fboquad;
    Cube m_cube;

    std::unique_ptr<QOpenGLFramebufferObject> m_fbo_front;
    std::unique_ptr<QOpenGLFramebufferObject> m_fbo_back;

    std::unique_ptr<QOpenGLShaderProgram> m_pre_pass_program;
    std::unique_ptr<QOpenGLShaderProgram> m_volume_pass_program;

    GLuint m_volume_tex_id {0};

    //TODO: Move volume data to its own class
    int dim_x {0};
    int dim_y {0};
    int dim_z {0};
    std::vector<GLubyte> volume_data;
};

#endif // VOLUMERENDER_H

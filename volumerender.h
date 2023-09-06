#ifndef VOLUMERENDER_H
#define VOLUMERENDER_H

#include <vector>
#include <memory>
#include <QMatrix4x4>

#include "fboquad.h"
#include "cube.h"
#include "camera.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLFramebufferObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class VolumeData;

class VolumeRender
{
public:
    VolumeRender();
    ~VolumeRender();

    void init();
    void render();
    void resize(int width, int height);

    void SetRayStepSize(const float &ray_step_size);
    void SetMaxRayIterations(const int &max_ray_iter);
private:
    void createFBOs();
    void createTextureVolume();

    void fboDrawVolumeFront();

    void fboDrawVolumeBack();

    // cull_facing_mode can be GL_FRONT or GL_BACK
    void fboPrePass(GLenum cull_facing_mode);

    void volumePass();

private:
    int m_width {0};
    int m_height {0};

    FboQuad m_fboquad;
    Cube m_cube;

    std::unique_ptr<Camera> m_camera;

    std::unique_ptr<QOpenGLFramebufferObject> m_fbo_front;
    std::unique_ptr<QOpenGLFramebufferObject> m_fbo_back;

    std::unique_ptr<QOpenGLShaderProgram> m_pre_pass_program;
    std::unique_ptr<QOpenGLShaderProgram> m_volume_pass_program;

    std::unique_ptr<VolumeData> m_volume_data;

    GLuint m_volume_tex_id {0};

    float m_ray_step_size {0.1};
    int m_ray_max_iter {256};
};

#endif // VOLUMERENDER_H

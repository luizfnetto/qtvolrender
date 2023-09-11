#ifndef VOLUMERENDERVIEWER_H
#define VOLUMERENDERVIEWER_H

#include <memory>

class VolumeRender;

class VolumeRenderViewer
{
public:
    VolumeRenderViewer();
    ~VolumeRenderViewer();

    void render();
    void resize(int width, int height);


    void setShaderStepSize(float stepsize);
    float getShaderStepSize();
    std::tuple<float, float> getShaderStepSizeLimits();

    void setShaderTotalSteps(int steptotal);
    int getShaderTotalSteps();
    std::tuple<int, int> getShaderTotalStepsLimits();

private:
    std::unique_ptr<VolumeRender> m_volume_render;

    float m_min_stepsize = {0.001f};
    float m_max_stepsize = {0.1f};
    float m_stepsize = {0.01};

    int m_max_stepnum = {2048};
    int m_min_stepnum = {64};
    int m_stepnum = {256};
};

#endif // VOLUMERENDERVIEWER_H

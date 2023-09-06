#include "volumerenderviewer.h"

#include "volumerender.h"

using namespace std;

VolumeRenderViewer::VolumeRenderViewer()
{
}

VolumeRenderViewer::~VolumeRenderViewer()
{

}

void VolumeRenderViewer::render()
{
    if (!m_volume_render) {
        m_volume_render = make_unique<VolumeRender>();
        m_volume_render->init();
    }

    m_volume_render->SetRayStepSize(m_stepsize);
    m_volume_render->SetMaxRayIterations(m_stepnum);
    m_volume_render->render();
}

void VolumeRenderViewer::resize(int width, int height)
{
    if (!m_volume_render)
        return;

    m_volume_render->resize(width, height);
}

void VolumeRenderViewer::setShaderStepSize(int stepsize_percent)
{
    float p = static_cast<float>(stepsize_percent)/100.f;

    if (p < 0.f)
        p = 0.f;

    if (p > 1.f)
        p = 1.f;

    m_stepsize = p*(m_max_stepsize - m_min_stepsize) + m_min_stepsize;
    qDebug() << m_stepsize;
}

int VolumeRenderViewer::getShaderStepSize()
{
    float pct = (m_stepsize - m_min_stepsize)/(m_max_stepsize - m_min_stepsize);
    return static_cast<int>(pct*100.f);
}

std::tuple<float, float, float> VolumeRenderViewer::getShaderStepSizeParams() {
    return std::tuple<float, float, float>(m_min_stepsize, m_max_stepsize, m_stepsize);
}

void VolumeRenderViewer::setShaderTotalSteps(int steps_percent)
{
    float p = static_cast<float>(steps_percent)/100.f;

    if (p < 0.f)
        p = 0.f;

    if (p > 1.f)
        p = 1.f;

    float min = static_cast<float>(m_min_stepnum);
    float max = static_cast<float>(m_max_stepnum);
    float v = p*(max - min) + min;
    m_stepnum = static_cast<int>(v);
    qDebug() << "setShaderTotalSteps" << m_stepnum;
}

int VolumeRenderViewer::getShaderTotalSteps()
{
    float min = static_cast<float>(m_min_stepnum);
    float max = static_cast<float>(m_max_stepnum);
    float v = static_cast<float>(m_stepnum);

    v = (v - min)/(max - min);

    return static_cast<int>(v*100.f);
}

std::tuple<int, int, int> VolumeRenderViewer::getShaderTotalStepsParams()
{
    return std::tuple<int, int, int>(m_min_stepnum, m_max_stepnum, m_stepnum);
}





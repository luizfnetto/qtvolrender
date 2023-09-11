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

void VolumeRenderViewer::setShaderStepSize(float stepsize)
{
    if (stepsize < m_min_stepsize)
        m_stepsize = m_min_stepsize;
    else if (stepsize > m_max_stepsize)
        m_stepsize = m_max_stepsize;
    else
        m_stepsize = stepsize;

    qDebug() << "setShaderStepSize: " << m_stepsize;
}

float VolumeRenderViewer::getShaderStepSize()
{
    return m_stepsize;
}

std::tuple<float, float> VolumeRenderViewer::getShaderStepSizeLimits() {
    return std::tuple<float, float>(m_min_stepsize, m_max_stepsize);
}

void VolumeRenderViewer::setShaderTotalSteps(int steptotal)
{
    if (steptotal < m_min_stepnum)
        m_stepnum  = m_min_stepnum;
    else if (steptotal > m_max_stepnum)
        m_stepnum = m_max_stepnum;
    else
        m_stepnum = steptotal;

    qDebug() << "setShaderTotalSteps: " << m_stepnum;
}

int VolumeRenderViewer::getShaderTotalSteps()
{
    return m_stepnum;
}

std::tuple<int, int> VolumeRenderViewer::getShaderTotalStepsLimits()
{
    return std::tuple<int, int>(m_min_stepnum, m_max_stepnum);
}

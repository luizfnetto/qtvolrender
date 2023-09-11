#include "mainwindow.h"
#include "glwidget.h"

#include "volumerenderviewer.h"
#include "dockwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_glwidget = new GLWidget(qRgb(20, 20, 50));
    setCentralWidget(m_glwidget);

    createDockWindows();
}


MainWindow::~MainWindow()
{
}

void MainWindow::setStepSizeValue(float stepsize)
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return;

    vrv->setShaderStepSize(stepsize);
    m_dock->updateLineEditStepSize();
}

void MainWindow::setStepTotalValue(int steptotal)
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return;

    vrv->setShaderTotalSteps(steptotal);
    m_dock->updateLineEditStepTotal();
}

std::tuple<float, float> MainWindow::getStepSizeLimits()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return std::tuple<float, float>(0, 0);
    return vrv->getShaderStepSizeLimits();
}

float MainWindow::getStepSizeValue()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return -1;
    return vrv->getShaderStepSize();
}

std::tuple<int, int> MainWindow::getTotalStepLimits()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return std::tuple<int, int>(0, 0);
    return vrv->getShaderTotalStepsLimits();
}

int MainWindow::getStepTotalValue()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return -1;
    return vrv->getShaderTotalSteps();
}

void MainWindow::createDockWindows()
{
    m_dock = new DockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, m_dock);
    m_dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dock->setFloating(false);
    m_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
}

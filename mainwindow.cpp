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

void MainWindow::setStepSizeValue(int v)
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return;

    vrv->setShaderStepSize(v);
    m_dock->setStepSizeLabels(this);
}

void MainWindow::setTotalStepsValue(int v)
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return;

    vrv->setShaderTotalSteps(v);
    m_dock->setTotalStepsLabels(this);
}

std::tuple<float, float, float> MainWindow::getStepSizeParams()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return std::tuple<float, float, float>(0, 0,0);
    return vrv->getShaderStepSizeParams();
}

int MainWindow::getStepSizeValue()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return -1;
    return vrv->getShaderStepSize();
}

std::tuple<int, int, int> MainWindow::getTotalStepParams()
{
    VolumeRenderViewer *vrv = m_glwidget->getVolumeRenderViewer();
    if (!vrv)
        return std::tuple<int, int, int>(0, 0,0);
    return vrv->getShaderTotalStepsParams();
}

int MainWindow::getTotalStepsValue()
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



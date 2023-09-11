#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLWidget;
class DockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    std::tuple<float, float> getStepSizeLimits();
    float getStepSizeValue();
    void setStepSizeValue(float stepsize);

    std::tuple<int, int> getTotalStepLimits();
    int getStepTotalValue();
    void setStepTotalValue(int steptotal);

private:
    void createDockWindows();

private:
    GLWidget *m_glwidget;
    DockWidget *m_dock;
};
#endif // MAINWINDOW_H

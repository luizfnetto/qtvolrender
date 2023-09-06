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


    std::tuple<float, float, float> getStepSizeParams();
    int getStepSizeValue();
    void setStepSizeValue (int v);

    std::tuple<int, int, int> getTotalStepParams();
    int getTotalStepsValue();
    void setTotalStepsValue (int v);
private:
    void createDockWindows();

private:
    GLWidget *m_glwidget;
    DockWidget *m_dock;
};
#endif // MAINWINDOW_H

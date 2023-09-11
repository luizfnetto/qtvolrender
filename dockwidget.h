#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>

class MainWindow;

namespace Ui {
class DockWidget;
}

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(MainWindow *parent = nullptr);
    ~DockWidget();

    void updateLineEditStepSize();
    void updateLineEditStepTotal();

private:
    void setupStepsLineEditValidators();

    void lineEditStepSizeChanged();
    void lineEditStepTotalChanged();

    void setSliderStepSize(float v);
    void sliderStepSizeChanged(int percent);

    void setSliderStepTotal(int v);
    void sliderStepTotalChanged(int percent);

private:
    Ui::DockWidget *m_ui {nullptr};
    MainWindow *m_parent {nullptr};
};

#endif // DOCKWIDGET_H

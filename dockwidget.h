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

    void setStepSizeLabels(MainWindow *parent = nullptr);
    void setTotalStepsLabels(MainWindow *parent = nullptr);

private:
    void setStepSizeValue (int v);
    void setTotalStepsValue (int v);

private:
    Ui::DockWidget *ui;
};

#endif // DOCKWIDGET_H

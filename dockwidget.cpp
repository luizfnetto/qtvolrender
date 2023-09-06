#include "dockwidget.h"
#include "ui_dockwidget.h"
#include "mainwindow.h"

DockWidget::DockWidget(MainWindow *parent) :
    QDockWidget(parent),
    ui(new Ui::DockWidget)
{
    ui->setupUi(this);
    qDebug() << "Constructor" << parent->getStepSizeValue();
    ui->sliderStepSize->setValue(parent->getStepSizeValue());
    ui->sliderTotalSteps->setValue(parent->getTotalStepsValue());
    connect(ui->sliderStepSize, &QSlider::valueChanged, parent, &MainWindow::setStepSizeValue);
    connect(ui->sliderTotalSteps, &QSlider::valueChanged, parent, &MainWindow::setTotalStepsValue);

    setStepSizeLabels(parent);
    setTotalStepsLabels(parent);
}

DockWidget::~DockWidget()
{
    delete ui;
}

void DockWidget::setStepSizeLabels(MainWindow *parent)
{
    auto [min, max, curr] = parent->getStepSizeParams();

    ui->lbMinStepsize->setText(QString::number(min));
    ui->lbMaxStepsize->setText(QString::number(max));
    ui->lbCurStepsize->setText(QString::number(curr));
}

void DockWidget::setTotalStepsLabels(MainWindow *parent)
{
    auto [min, max, curr] = parent->getTotalStepParams();

    ui->lbMinStepnum->setText(QString::number(min));
    ui->lbMaxStepnum->setText(QString::number(max));
    ui->lbCurStepnum->setText(QString::number(curr));
}

#include "dockwidget.h"
#include "ui_dockwidget.h"
#include "mainwindow.h"

#include <QDoubleValidator>
#include <QIntValidator>

DockWidget::DockWidget(MainWindow *parent)
    : QDockWidget(parent)
    , m_ui(new Ui::DockWidget)
    , m_parent(parent)
{
    m_ui->setupUi(this);

    setSliderStepSize(parent->getStepSizeValue());
    setSliderStepTotal(parent->getStepTotalValue());

    connect(m_ui->sliderStepSize, &QSlider::valueChanged, this, &DockWidget::sliderStepSizeChanged);
    connect(m_ui->sliderStepTotal, &QSlider::valueChanged, this, &DockWidget::sliderStepTotalChanged);

    connect(m_ui->leCurStepSize, &QLineEdit::editingFinished, this, &DockWidget::lineEditStepSizeChanged);
    connect(m_ui->leCurStepTotal, &QLineEdit::editingFinished, this, &DockWidget::lineEditStepTotalChanged);

    auto [ssmin, ssmax] = m_parent->getStepSizeLimits();
    m_ui->lbMinStepSize->setText(QString::number(ssmin));
    m_ui->lbMaxStepSize->setText(QString::number(ssmax));

    auto [stmin, stmax] = m_parent->getTotalStepLimits();
    m_ui->lbMinStepTotal->setText(QString::number(stmin));
    m_ui->lbMaxStepTotal->setText(QString::number(stmax));

    updateLineEditStepSize();
    updateLineEditStepTotal();

    setupStepsLineEditValidators();
}

DockWidget::~DockWidget()
{
}

void DockWidget::updateLineEditStepSize()
{
    float v = m_parent->getStepSizeValue();
    //setText doesnt trigger the signal editingFinished
    m_ui->leCurStepSize->setText(QString::number(v));
}

void DockWidget::updateLineEditStepTotal()
{
    int v = m_parent->getStepTotalValue();
    //setText doesnt trigger the signal editingFinished
    m_ui->leCurStepTotal->setText(QString::number(v));
}

void DockWidget::setupStepsLineEditValidators()
{
    auto [step_size_min, step_size_max] = m_parent->getStepSizeLimits();
    QDoubleValidator *step_size_validator = new QDoubleValidator(step_size_min, step_size_max, 7, this);
    m_ui->leCurStepSize->setValidator(step_size_validator);

    auto [step_total_min, step_total_max] = m_parent->getTotalStepLimits();
    QIntValidator *step_total_validator = new QIntValidator(step_total_min, step_total_max, this);
    m_ui->leCurStepTotal->setValidator(step_total_validator);
}

void DockWidget::lineEditStepSizeChanged()
{
    qDebug() << "lineEditStepSizeChanged "<< m_ui->leCurStepSize->text();

    bool ok = false;
    float value = m_ui->leCurStepSize->text().toFloat(&ok);
    if (ok)
        m_parent->setStepSizeValue(value);
}

void DockWidget::lineEditStepTotalChanged()
{
    qDebug() << "lineEditStepTotalChanged " << m_ui->leCurStepTotal->text();

    bool ok = false;
    int value = m_ui->leCurStepTotal->text().toInt(&ok);
    if (ok)
        m_parent->setStepTotalValue(value);
}

void DockWidget::setSliderStepSize(float v)
{
    auto [step_size_min, step_size_max] = m_parent->getStepSizeLimits();

    float frac = (v - step_size_min)/(step_size_max - step_size_min);

    m_ui->sliderStepSize->setValue(static_cast<int>(frac*100.f));
}

void DockWidget::sliderStepSizeChanged(int percent)
{
    auto [step_size_min, step_size_max] = m_parent->getStepSizeLimits();

    float p = static_cast<float>(percent)/100.f;
    float stepsize = p*(step_size_max - step_size_min) + step_size_min;

    m_parent->setStepSizeValue(stepsize);
}

void DockWidget::setSliderStepTotal(int v)
{
    auto [step_total_min, step_total_max] = m_parent->getTotalStepLimits();

    float min = static_cast<float>(step_total_min);
    float max = static_cast<float>(step_total_max);
    float frac = (static_cast<float>(v) - min)/(max - min);

    m_ui->sliderStepTotal->setValue(static_cast<int>(frac*100.f));
}

void DockWidget::sliderStepTotalChanged(int percent)
{
    auto [step_total_min, step_total_max] = m_parent->getTotalStepLimits();

    float p = static_cast<float>(percent)/100.f;
    float min = static_cast<float>(step_total_min);
    float max = static_cast<float>(step_total_max);
    int steptotal = static_cast<int>(p*(max - min) + min);

    m_parent->setStepTotalValue(steptotal);
}

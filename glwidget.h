#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <memory>

#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

#include "volumerender.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLBuffer)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT // enabled meta object abilities
public:
    GLWidget(const QColor &background);
    ~GLWidget();

protected:
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;

private:
    void reset();
    void updateWinSize();

    std::unique_ptr<VolumeRender> m_volume_render;

    QColor m_background;
    QMetaObject::Connection m_contextWatchConnection;
};

#endif // GLWIDGET_H

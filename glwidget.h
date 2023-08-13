#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT // enabled meta object abilities
public:
    GLWidget(const QColor &background);
    ~GLWidget();

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    QColor m_background;
    QMetaObject::Connection m_contextWatchConnection;
};

#endif // GLWIDGET_H

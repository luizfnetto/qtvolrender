#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Qt Volume Rendering Test");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    // Request OpenGL 3.3 core or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        format.setVersion(3, 3);
        format.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.0 context");
        format.setVersion(3, 0);
    }

    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    //w.showMaximized();
    w.resize(800, 600);
    w.show();
    return a.exec();
}

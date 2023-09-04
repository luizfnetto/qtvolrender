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
    w.resize(800, 600);

// TODO: [Netto]
// QT may have some bug when initializing maximized or with a size bigger than the available
// The resizeCB is not called and the internal glViewport is outdated in the first frame
// Quick and dirt fix is to skip the first paintGL call (?)
// Other approach is to check through glviewport the size every redraw (expensive) or from time to
// time (?)
// Skipping the first frame fix the initialization but not when we manually set fullscreen from a
// smaller window
//
// Maybe I'm skipping some step when setting up the window?
// Uncomment the first or second line below to check
//    w.showMaximized();
//    w.showFullScreen();
//    w.resize(1600, 1200);

    w.show();
    return a.exec();
}

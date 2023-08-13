#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Qt Volume Rendering Test");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    MainWindow w;
    w.resize(1280, 720);
    w.show();
    return a.exec();
}

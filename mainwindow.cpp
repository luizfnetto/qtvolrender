#include "mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    GLWidget *glwidget = new GLWidget(qRgb(20, 20, 50));
    setCentralWidget(glwidget);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumHeight(580);
    w.setMinimumWidth(640);
    w.show();

    return a.exec();
}

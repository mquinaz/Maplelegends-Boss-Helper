#include "mainwindow.h"

#include "timer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Timer t;

    w.show();
    return a.exec();
}

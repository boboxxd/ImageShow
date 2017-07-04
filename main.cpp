#include "mainwindow.h"
#include <QApplication>
#include "common.h"
#include <QDebug>
#include "readtext.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}

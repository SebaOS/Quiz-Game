#include <QApplication>
#include <iostream>
#include "start.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
    w.show();

    return a.exec();


}


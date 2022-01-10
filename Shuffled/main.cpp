#include "mainwindow.h"
#include "AdjList.h"
#include<fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

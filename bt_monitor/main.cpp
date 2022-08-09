#include "mainwindow.h"
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#include <QApplication>
#include "utils.h"

using std::chrono_literals::operator""s;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("BT-Monitor");
    w.show();
    w.drawSomething();

    return a.exec();
}

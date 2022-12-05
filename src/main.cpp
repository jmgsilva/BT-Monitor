#include "mainwindow.h"
#include <QApplication>


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

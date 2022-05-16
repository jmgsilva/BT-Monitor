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

    //std::string tree = "Fallback:fb1(Sequence:seq1(Action:a1,Fallback:fb2(Action:a2,Action:a3)),Parallel:par1(Action:a4,Action:a10),Sequence:seq2(Action:a5,Fallback:fb3(Action:a6,Action:a7,Action:a8,Action:a9)))/";
    //getBehaviorTreeFromString(tree);
    //socket.recv(request, zmq::recv_flags::none);

    //message = request.to_string();
    //getBehaviorTreeFromString(message);
    //orderTree();

    w.show();
    w.drawSomething();

    return a.exec();
}

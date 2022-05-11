#include "mainwindow.h"
#include <zmq.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#include <QApplication>
#include "utils.h"

using std::chrono_literals::operator""s;

int main(int argc, char *argv[])
{
    /*// initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{context, zmq::socket_type::rep};
    //socket.bind("tcp:/:5555");

    // prepare some static data for responses
    const std::string data{"World"};

    for (;;)
    {
        std::cout << "Oi" << std::endl;
        zmq::message_t request;

        // receive a request from client
        socket.recv(request, zmq::recv_flags::none);

        // simulate work
        std::this_thread::sleep_for(1s);

        // send the reply to the client
        socket.send(zmq::buffer(data), zmq::send_flags::none);
    }*/


    QApplication a(argc, argv);
    MainWindow w;

    std::string tree = "Fallback:fb1(Sequence:seq1(Action:a1,Fallback:fb2(Action:a2,Action:a3)),Parallel:par1(Action:a4,Action:a10),Sequence:seq2(Action:a5,Fallback:fb3(Action:a6,Action:a7,Action:a8,Action:a9)))/";
    getBehaviorTreeFromString(tree);
    orderTree();

    w.show();
    w.drawSomething();
    return a.exec();
}

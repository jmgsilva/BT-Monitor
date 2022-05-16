#ifndef ZMQSERVER_H
#define ZMQSERVER_H

#include <zmq.hpp>
#include <QThread>

class ZMQServer : public QThread {
    Q_OBJECT

    QThread th;

    zmq::context_t context;
    zmq::socket_t socket;

    zmq::message_t request;

    //const std::string reply;

public:
    ZMQServer();
    void run() override;

signals:
    void messageReceived(const std::string messsage);
};

#endif // ZMQSERVER_H

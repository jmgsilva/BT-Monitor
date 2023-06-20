#ifndef ZMQPULLER_H
#define ZMQPULLER_H

#include <zmq.hpp>
#include <QThread>

class ZMQPuller : public QThread {
    Q_OBJECT
    zmq::context_t *context;
    zmq::socket_t *socket;

public:
    ZMQPuller();
    ZMQPuller(std::string port);
    void run() override;

signals:
    void messageReceived(const std::string messsage);
};

#endif // ZMQPULLER_H

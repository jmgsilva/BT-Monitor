#include "zmqserver.h"
#include <iostream>

ZMQPuller::ZMQPuller() {
    context = new zmq::context_t(1);
    socket = new zmq::socket_t(*context, zmq::socket_type::pull);
    socket->bind("tcp://*:5555");
    //socket->set(zmq::sockopt::subscribe, "");
}

void ZMQPuller::run() {
    for (;;)
    {
        zmq::message_t message_received;
        zmq::recv_result_t recv_result = socket->recv(message_received, zmq::recv_flags::none);

        std::string string_received = message_received.to_string();

        emit messageReceived(string_received);
    }
}

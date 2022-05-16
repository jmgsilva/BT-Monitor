#include "zmqserver.h"

ZMQServer::ZMQServer() {
    context = zmq::context_t{1};
    socket = zmq::socket_t{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");
}

void ZMQServer::run() {
    for (;;)
    {
        std::string message;

        // receive a request from client
        socket.recv(request, zmq::recv_flags::none);

        // work
        message = request.to_string();

        emit messageReceived(message);

        // send the reply to the client (MANDATORY)
        socket.send(zmq::buffer("ACK"), zmq::send_flags::none);
    }
}

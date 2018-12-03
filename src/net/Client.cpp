#include <iostream>
#include <stdexcept>
#include <memory>               // shared_ptr
#include <errno.h>
#include <string.h>
#include "Client.h"

const int TIMEOUT = 1;

Client::Client(const std::string &_host, int _port) :
    host(_host),
    port(_port),
    socket() {}

void Client::JoinTheGame() {
    try {
        socket.connect(host, port);
    } catch (const std::exception &ex) {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        throw std::runtime_error("Connection error");
    }

//    socket.setNonBlocked(true);
}

std::string Client::GetGameSituation() {
//    std::string msg;
//    read(socket, &msg, sizeof(msg));
//    socket.setNonBlocked(true);
    return socket.recvTimed(5);
}

void Client::SendNewStep(const std::string& command) {
    socket.send(command);
}

Client::~Client() {
    socket.close();
}

Client& Client::getInstance(const std::string& _host, int _port) {
    static Client instance(_host, _port);
    return instance;
}

//int main(int argc, char *argv[]) {
//    if (argc != 3) {
//        std::cerr << "usage: " << argv[0] << " host port" << std::endl;
//        return 0;
//    }
//
//    try {
//        std::string host(argv[1]);
//        int port = std::stoi(argv[2]);
//
//        Socket s;
//        s.connect(host, port, /*timeout, sec*/5);
//
//        s.send("It works");
//
//    } catch (const std::exception &e) {
//        std::cerr << "ERROR: " << e.what() << std::endl;
//    }
//
//    return 0;
//}
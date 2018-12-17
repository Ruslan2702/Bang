#include <iostream>
#include <stdexcept>
#include <memory>
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

    socket.setNonBlocked(true);
}

std::string Client::GetGameSituation() {
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

void Client::GetFirstMessage(char* nowPlayers, char* myID) {
  std::string msg = socket.recvTimed(5);
  *myID = msg[0];
  *nowPlayers = msg[1];
}

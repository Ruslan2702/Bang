//
// Created by ruslan on 11.11.18.
//

#ifndef BANG_CLIENT_H
#define BANG_CLIENT_H


#include <string>
#include "socket.hpp"


class Client {
public:
    Client(const std::string& _host, int _port);
    void JoinTheGame();
    void GetFirstMessage();
    std::string GetGameSituation();
    void SendNewStep(const std::string& command);
    void DrowWindow();
    ~Client();

private:
    Socket socket;
    std::string host;
    int port;
    int playerID;
};



#endif //BANG_CLIENT_H

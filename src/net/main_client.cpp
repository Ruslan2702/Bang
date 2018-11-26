//
// Created by ruslan on 10.11.18.
//

#include <iostream>
#include "Client.h"
#include "../window/Window.h"
#include <fstream>


int main(int argv, char** argc) {
//    std::cout << "Client started!" << std::endl;

    Window window;
    std::string host;
    int port = 0;
    window.HelloMessage(host, &port);

//    Client client(host.c_str(), port);


//    client.JoinTheGame();
    window.YouAreConnected();
//    client.SendNewStep("First step in this game");
    window.GameInfoMessage();
    window.UpgradeWindowByNewStep();
    window.YourTurn();
//    std::cout << client.GetGameSituation() << std::endl;
//    std::cout << "Client works!" << std::endl;

    return 0;
}
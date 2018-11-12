//
// Created by ruslan on 10.11.18.
//

#include <iostream>
#include "Client.h"


int main(int argv, char** argc) {
    std::cout << "Client works!" << std::endl;
    Client client("127.0.0.1", 8888);
    client.JoinTheGame();
    client.SendNewStep("First step in this game");
    std::cout << client.GetGameSituation() << std::endl;
    std::cout << "Client works!" << std::endl;
    return 0;
}
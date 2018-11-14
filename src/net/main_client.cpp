//
// Created by ruslan on 10.11.18.
//

#include <iostream>
#include "Client.h"
#include "../window/Window.h"
#include <fstream>


int main(int argv, char** argc) {
    std::cout << "Client started!" << std::endl;

    Window window;
    std::string host = "";
    int port = 0;
    window.HelloMessage(host, &port);

    std::ofstream fout("cppstudio.txt");

    fout << host.c_str() << " " << port;
    fout.close();

//    host = "127.0.0.1";
//    port = 8888;

//    printw(host.c_str());
//    printw("%d", port);

    Client client(host.c_str(), port);


    client.JoinTheGame();
    client.SendNewStep("First step in this game");
    std::cout << client.GetGameSituation() << std::endl;
    std::cout << "Client works!" << std::endl;

    return 0;
}
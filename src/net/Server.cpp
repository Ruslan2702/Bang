//
// Created by Андрей on 29.10.18.
//

#include <iostream>
#include <stdexcept>
#include <thread>
//#include "socket.hpp"
#include "Server.h"
#include <vector>


int MAX_CONNECT = 2;

void send_hellow_msg(std::vector<std::shared_ptr<Socket>> const &clients) {

    std::string hellow_msg = "HELLOW";

    for (auto client : clients) {
        client->send(hellow_msg);
    }
}

void client_work(std::shared_ptr<Socket> client)
{
    client->setRcvTimeout(/*sec*/30, /*microsec*/0);
    while (true) try
        {
            std::string line = client->recv();
            client->send("echo: " + line + "\n");
        }
        catch(const std::exception &e)
        {
            std::cerr << "exception: " << e.what() << std::endl;
            return;
        }
}

int main(int argc, char *argv[]) /// запуск сервера
{
//    if (argc != 2) /// проверка количества аргументов
//    {
//        std::cerr << "usage: " << argv[0] << " port" << std::endl;
//        return 0;
//    }

//    int port = std::stoi(std::string(argv[1])); ///Извлекает знаковое целое число из строки str.

    int port = std::stoi(std::string("5555"));

    try
    {
        Socket s;
        s.createServerSocket(port, 1); /// не уверен, то 1

        std::vector<std::shared_ptr<Socket>> clients;

        for (int i = 0; i < MAX_CONNECT; ++i) {
            std::shared_ptr<Socket> client = s.accept();
            clients.push_back(client);
        }

        std::cout << "THERE ARE " << MAX_CONNECT << " CON" << std::endl;

        for (auto client : clients) client->send("HELLOW");

        while(true)
        {

        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

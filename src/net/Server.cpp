//
// Created by Андрей on 29.10.18.
//

#include <iostream>
#include <stdexcept>
#include <thread>
#include "Server.h"
#include <vector>


int MAX_CONNECT = 2;
int TIME_TO_MOVE_SEC = 30;
int TIME_TO_MOVE_MSEC = 0;

Server::Server(std::string const  &port, int const &queue_size) noexcept(false) {
    server_socket = Socket();
    server_socket.createServerSocket(std::stoi(port), queue_size);
}

void Server::send_hellow_msg() {

    std::string hellow_msg = "HELLOW\n";

    for (auto client : clients) {
        client->send(hellow_msg);
    }
}

void Server::client_work(std::shared_ptr<Socket> client) {

}

void Server::get_players(int MAX_CONNECT) {
    for (int i = 0; i < MAX_CONNECT; ++i) {
            std::shared_ptr<Socket> client = server_socket.accept();
            clients.push_back(client);
        }
}

void Server::send_everybode_step(std::string step) noexcept(false) {
    for (auto client : clients) client->send(step + "\n");
}

std::string Server::get_step(int index_client) { /// Step
    clients[index_client]->setRcvTimeout(TIME_TO_MOVE_SEC, TIME_TO_MOVE_MSEC);

    std::string line = clients[index_client]->recv();
//    std::cout << line << std::endl;
    return line;
}

int main(int argc, char *argv[]) /// запуск сервера
{
    try
    {
        Server server("5555", MAX_CONNECT);
        server.get_players(MAX_CONNECT);
        server.send_hellow_msg();

        std::cout << "THERE ARE " << MAX_CONNECT << " CON" << std::endl;

        while(true)
        {
            for (int i = 0; i < MAX_CONNECT; ++i) {
                std::string step = server.get_step(i);
                server.send_everybode_step(step);
            }
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

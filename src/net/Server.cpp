//
// Created by Андрей on 29.10.18.
//

#include <iostream>
#include <stdexcept>
#include <thread>
#include "Server.h"
#include <vector>
#include "../parsers/SituationParser.h"
#include "../parsers/StepParser.h"

int MAX_CONNECT = 2;
int TIME_TO_MOVE_SEC = 30;
int TIME_TO_MOVE_MSEC = 0;

void Server::send_end_msg(std::string winner) noexcept(false) {
    std::string answer = winner + "- WIN!";

    for (auto client : clients) client->send(answer);
}

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

void Server::send_current_situation(std::string const &msg) {
    for (auto client : clients) client->send(msg);
}

void Server::client_work(std::shared_ptr<Socket> client) {
}

void Server::get_players(int MAX_CONNECT) {
    for (int i = 0; i < MAX_CONNECT; ++i) {
        std::shared_ptr<Socket> client = server_socket.accept();
        clients.push_back(client);

        std::string id_msg = std::to_string(i) + " " + std::to_string(i + 1) + "\n" ;

        client->send(id_msg);
    }
}

void Server::send_everybode_step(std::string step) noexcept(false) {
    for (auto client : clients) client->send(step + "\n");
}

std::string Server::get_step(int index_client) {
    clients[index_client]->setRcvTimeout(TIME_TO_MOVE_SEC, TIME_TO_MOVE_MSEC);

    std::string line = clients[index_client]->recv();
    return line;
}

std::string Server::upgrade_situation(Step const &step, GameManager &game_manager, GameSituation &current_sitution) {
}

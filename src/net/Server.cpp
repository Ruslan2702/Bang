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

void Server::insert_step_in_db(std::string const &step) noexcept(false) {
    return; /// пока база не прикручена
}

void Server::send_end_msg() noexcept(false) {
    for (auto client : clients) client->send("GAME END WIN ?????? \n");
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

void Server::send_current_situation(GameSituation const &curren_stuation) {
    return;
}

void Server::client_work(std::shared_ptr<Socket> client) {
    return;
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

std::string Server::get_step(int index_client) {
    clients[index_client]->setRcvTimeout(TIME_TO_MOVE_SEC, TIME_TO_MOVE_MSEC);

    std::string line = clients[index_client]->recv();
//    std::cout << line << std::endl;
    return line;
}

std::string Server::upgrade_situation(Step const &step, GameManager &game_manager, GameSituation &current_sitution) {
    return "";
}

int main(int argc, char *argv[]) /// запуск сервера
{
    try
    {
        SituationParser situationParser();
        StepParser stepParser();
        GameManager gameManager;

        Server server("5555", MAX_CONNECT);

        server.get_players(MAX_CONNECT);
        std::cout << "THERE ARE " << MAX_CONNECT << " CON" << std::endl;
        GameSituation current_sitution;

        server.send_hellow_msg();
        server.send_current_situation(current_sitution);

        int game_move = 0;
        std::string WINNER;
        while(WINNER == "")
        {
            std::string step = server.get_step(game_move % MAX_CONNECT);
            /// проверка валидности степа
            Step valid_step; /// dummy
            WINNER = server.upgrade_situation(valid_step, gameManager, current_sitution);

            server.send_everybode_step(step);
            server.send_current_situation(current_sitution);
            server.insert_step_in_db(step);

            ++game_move;
        }

        server.send_end_msg();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

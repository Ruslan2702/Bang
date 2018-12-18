//
// Created by Андрей on 29.10.18.
//

#ifndef CPPPROJECT_SERVER_H
#define CPPPROJECT_SERVER_H

#include <iostream>
#include <stdexcept>
#include <thread>
#include "socket.hpp"
#include <vector>
#include "../logic/GameSituation.h"
#include "../logic/Step.h"
#include "../logic/GameManager.h"

const int END_GAME = -1;

class Server {
public:
    Server() = delete;
    explicit Server(std::string const  &port, int const &queue_size) noexcept(false);

    void client_work(std::shared_ptr<Socket> client);
    void send_hellow_msg();
    void send_current_situation(std::string const &msg);
    void get_players(int MAX_CONNECT) noexcept(false);
    std::string get_step(int index_client) noexcept(false);
    void send_everybode_step(std::string step) noexcept(false);
    std::string upgrade_situation(Step const &step, GameManager &game_manager,
                                  GameSituation &current_sitution);

    void send_end_msg(std::string winner) noexcept(false);

private:

    Socket server_socket;
    std::vector<std::shared_ptr<Socket>> clients;
};

void insert_step_in_db(Step const &step);

#endif //CPPPROJECT_SERVER_H

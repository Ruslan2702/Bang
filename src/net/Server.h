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

const int END_GAME = -1;

class Server {
public:
    Server() = delete;
    explicit Server(std::string const  &port, int const &queue_size) noexcept(false);
//    ~Server();

    void client_work(std::shared_ptr<Socket> client);
    void send_hellow_msg();
    void send_current_situation(GameSituation const &curren_stuation,
                                std::vector<std::shared_ptr<Socket>> const &clients
    );
    void get_players(int MAX_CONNECT) noexcept(false);
    std::string get_step(int index_client) noexcept(false); /// Step
    void send_everybode_step(std::string step) noexcept(false);
    void new_cards_for_user(GameSituation &curren_stuation);
    int upgrade_situation(GameSituation &curren_stuation, Step const &step);  /// -1, если игра закончилась
    void send_end_msg(std::vector<std::shared_ptr<Socket>> const &clients) noexcept(false);
    void insert_step_in_db(Step const &step) noexcept(false);

private:
    Socket server_socket;
    std::vector<std::shared_ptr<Socket>> clients;
};

void insert_step_in_db(Step const &step);

#endif //CPPPROJECT_SERVER_H

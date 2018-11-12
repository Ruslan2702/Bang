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

void client_work(std::shared_ptr<Socket> client);

void send_hellow_msg(std::vector<std::shared_ptr<Socket>> const &clients);

void send_current_situation(GameSituation const &curren_stuation,
                            std::vector<std::shared_ptr<Socket>> const &clients
);

Step get_step(std::shared_ptr<Socket>);

void new_cards_for_user(GameSituation &curren_stuation);

int upgrade_situation(GameSituation &curren_stuation, Step const &step);  /// -1, если игра закончилась

void send_end_msg(std::vector<std::shared_ptr<Socket>> const &clients);

void insert_step_in_db(Step const &step);




#endif //CPPPROJECT_SERVER_H

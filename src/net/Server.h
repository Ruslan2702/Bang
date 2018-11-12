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
#include "../logic/PlayerInfo.h"

void client_work(std::shared_ptr<Socket> client);

void send_hellow_msg(std::vector<std::shared_ptr<Socket>> const & clients);

void send_current_situation(PlayerInfo const & situation,
                            std::vector<std::shared_ptr<Socket>> const & clients
);





#endif //CPPPROJECT_SERVER_H

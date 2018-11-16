//
// Created by Андрей on 12.11.18.
//

#ifndef BANG_GAMESITUATION_H
#define BANG_GAMESITUATION_H

#include "PlayerInfo.h"
#include <vector>
#include <iostream>

struct GameSituation {
    std::vector<std::shared_ptr<PlayerInfo>> player_list;
    bool is_end = 0;
    bool is_sherif = 1;
    bool is_renigan = 1;
    int count_bandits = 3;
    int count_sherifs_helpers = 1;
};

#endif //BANG_GAMESITUATION_H

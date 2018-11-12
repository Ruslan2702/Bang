//
// Created by Андрей on 12.11.18.
//

#ifndef BANG_GAMESITUATION_H
#define BANG_GAMESITUATION_H

#include "PlayerInfo.h"
#include <vector>

struct GameSituation {
    std::vector<std::shared_ptr<PlayerInfo>> player_list;
    bool is_end;
    bool is_sherif;
    bool is_renigan;
    int count_bandits;
    int count_sherifs_helpers;
};

#endif //BANG_GAMESITUATION_H

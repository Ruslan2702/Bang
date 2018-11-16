//
// Created by Андрей on 07.11.18.
//

#ifndef BANG_PLAYERINFO_H
#define BANG_PLAYERINFO_H

#include <vector>
#include "Card.h"
#include "Gun.h"

struct PlayerInfo {
    std::vector<Card> cards_in_hand;
    int HP;
    std::string role;
    std::string name;
    int range = 1;
    bool is_dead = 0;
};


#endif BANG_PLAYERINFO_H

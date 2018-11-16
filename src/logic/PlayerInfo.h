//
// Created by Андрей on 07.11.18.
//

#ifndef BANG_PLAYERINFO_H
#define BANG_PLAYERINFO_H

#include <vector>
#include "Card.h"
#include <iostream>

struct PlayerInfo {
    std::vector<Card> cards_in_hand;
    int HP;
    int MAX_XP = 4;
    std::string role;
    std::string name;
    int range = 1;
    bool is_dead = 0;
};


#endif BANG_PLAYERINFO_H

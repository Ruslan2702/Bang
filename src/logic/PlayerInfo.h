//
// Created by Андрей on 07.11.18.
//

#ifndef BANG_GAMESITUATION_H
#define BANG_GAMESITUATION_H

#include <vector>
#include "Card.h"
#include "Gun.h"

struct PlayerInfo {
    std::vector<Card> cards_in_hand;
    int HP;
    std::string role;
    std::string name;
    int range = 1;
    bool is_dead;
};


#endif //BANG_GAMESITUATION_H

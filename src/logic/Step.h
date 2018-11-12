//
// Created by Андрей on 12.11.18.
//

#ifndef BANG_STEP_H
#define BANG_STEP_H

#include "Card.h"

struct Step {
    std::string action;
    Card card;
    std::string on_player;
};

#endif //BANG_STEP_H

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
  int MAX_HP;
  std::string role;
  std::string name;
  int range = 1;
  int position;
  bool is_dead = false;
};

#endif BANG_PLAYERINFO_H

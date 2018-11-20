//
// Created by Андрей on 12.11.18.
//

#ifndef BANG_GAMESITUATION_H
#define BANG_GAMESITUATION_H

#include "PlayerInfo.h"
#include <vector>
#include <iostream>
#include <memory>

struct GameSituation {
  std::vector<std::shared_ptr<PlayerInfo>> player_list;
  bool is_end = false;
  bool sherif_alive = true;
  bool renigan_alive = true;
  int count_bandits = 3;
  int count_sherifs_helpers = 1;
  std::string WINNER = "";
};

#endif //BANG_GAMESITUATION_H

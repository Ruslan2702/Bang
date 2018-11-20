#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>
#include "GameSituation.h"

class GameManager {
 public:
  void bang(PlayerInfo player_from, PlayerInfo &player_to);
  bool can_bang(PlayerInfo player_from, PlayerInfo &player_to); /// расчет ренджи
  void drink_beer(PlayerInfo &player); /// пиво на себя полюбому
  bool is_miss(PlayerInfo player);
  void check_end_game();
  GameSituation get_situation();
  bool check_count_cards(PlayerInfo player); /// карт должно быть столько, сколько HP
  void add_2_cards_before_move(PlayerInfo &player); /// добавление 2 карт перед началом хода
  void gun(PlayerInfo &player); /// + 1 к радиуму поражен
  GameSituation set_situation();
  Card get_random_card();
  GameSituation current_situation;
  std::vector<Card> cards;
};

#endif //GAME_MANAGER_GAMEMANAGER_H

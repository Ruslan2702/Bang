#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>
#include "GameSituation.h"

class GameManager {
 public:
  void bang(std::shared_ptr<PlayerInfo> player_from, std::shared_ptr<PlayerInfo> player_to);
  bool can_bang(std::shared_ptr<PlayerInfo> player_from, std::shared_ptr<PlayerInfo> player_to) const; /// расчет ренджи
  void drink_beer(std::shared_ptr<PlayerInfo> player_to); /// пиво на себя полюбому
  bool player_have_card(std::shared_ptr<PlayerInfo> player, std::string card_name) const;
  void check_end_game();
  GameSituation get_situation();
  bool check_count_cards(std::shared_ptr<PlayerInfo> player_from) const; /// карт должно быть столько, сколько HP
  void add_2_cards_before_move(std::shared_ptr<PlayerInfo> player); /// добавление 2 карт перед началом хода
  void gun(std::shared_ptr<PlayerInfo> player); /// + 1 к радиуму поражен
  void drop_card(std::shared_ptr<PlayerInfo> player, std::string name);
  GameSituation set_situation();
  Card get_random_card();
  Card get_card(std::string name) const;
  std::shared_ptr<PlayerInfo> get_player(int player_id);
  GameSituation current_situation;
  std::vector<Card> cards;
};

#endif //GAME_MANAGER_GAMEMANAGER_H

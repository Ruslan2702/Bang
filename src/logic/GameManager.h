#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>
#include "GameSituation.h"

class GameManager {
 public:
  void bang(std::shared_ptr<PlayerInfo> player_from, std::shared_ptr<PlayerInfo> player_to);
  bool can_bang(std::shared_ptr<PlayerInfo> player_from, std::shared_ptr<PlayerInfo> player_to) const;
  void drink_beer(std::shared_ptr<PlayerInfo> player_to);
  bool player_have_card(std::shared_ptr<PlayerInfo> player, std::string card_name) const;
  void check_end_game();
  GameSituation get_situation();
  bool check_count_cards(std::shared_ptr<PlayerInfo> player_from) const;
  void add_2_cards_before_move(std::shared_ptr<PlayerInfo> player);
  void gun(std::shared_ptr<PlayerInfo> player);
  void drop_card(std::shared_ptr<PlayerInfo> player, std::string name);
  int get_count_alive_players() const;
  GameSituation set_situation();
  Card get_random_card();
  Card get_card(std::string name) const;
  std::shared_ptr<PlayerInfo> get_player(int player_id);
  GameSituation current_situation;
  std::vector<Card> cards;
};

#endif //GAME_MANAGER_GAMEMANAGER_H

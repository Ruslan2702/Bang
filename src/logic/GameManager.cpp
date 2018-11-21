#include "GameSituation.h"
#include "GameManager.h"
#include <algorithm>
#include <map>

void GameManager::bang(std::shared_ptr<PlayerInfo> player_from, std::shared_ptr<PlayerInfo> player_to) {
  if (can_bang(player_from, player_to)) {

    if (!(player_have_card(player_to, "[MISS]"))) {
      player_to->HP--;
      if (player_to->HP == 0) {
        player_to->is_dead = true;
        std::string role = player_to->role;
        if (role == "bandit")
          current_situation.count_bandits--;
        else if (role == "helper")
          current_situation.count_sherifs_helpers--;
        else if (role == "sheriff")
          current_situation.sherif_alive = false;
        else if (role == "rinnegan")
          current_situation.renigan_alive = false;
      }

    } else {

      drop_card(player_to, "[MISS]");

    }
    drop_card(player_from, "[BANG]");
    check_end_game();
  }
}

bool GameManager::can_bang(std::shared_ptr<PlayerInfo> player_from, std::shared_ptr<PlayerInfo> player_to) const {
  int count_players = get_count_alive_players();
  return ((player_from->range + player_from->position) >= player_to->position % count_players)
      and player_have_card(player_from, "[BANG]");
}

void GameManager::drink_beer(std::shared_ptr<PlayerInfo> player) {
  if (player_have_card(player, "[BEER]"))
    if (player->MAX_HP > player->HP) {
      player->HP++;
      drop_card(player, "[BEER]");
    }
}

GameSituation GameManager::get_situation() {
  GameSituation dummy;
  return dummy; /// dummy
}

bool GameManager::player_have_card(std::shared_ptr<PlayerInfo> player, std::string card_name) const {
  Card card;
  card = get_card(std::move(card_name));
  return player->cards_in_hand.end() != find(player->cards_in_hand.begin(), player->cards_in_hand.end(), card);
}

bool GameManager::check_count_cards(std::shared_ptr<PlayerInfo> player) const {
  return player->HP >= player->cards_in_hand.size(); /// dummy
}

void GameManager::add_2_cards_before_move(std::shared_ptr<PlayerInfo> player) {
  Card card_1 = get_random_card();
  Card card_2 = get_random_card();
  player->cards_in_hand.push_back(card_1);
  player->cards_in_hand.push_back(card_2);
}

void GameManager::gun(std::shared_ptr<PlayerInfo> player) {
  if (player_have_card(player, "[GUN]")) {
    player->range++;
    drop_card(player, "[GUN]");
  }
}

GameSituation GameManager::set_situation() {
  return GameSituation();
}

void GameManager::check_end_game() {
  if (!current_situation.sherif_alive && current_situation.count_bandits == 0) {
    current_situation.WINNER = "rinnegan";
    current_situation.is_end = true;
  }
  if (!current_situation.sherif_alive && !current_situation.renigan_alive) {
    current_situation.WINNER = "bandit";
    current_situation.is_end = true;
  }
  if (current_situation.count_bandits == 0 && !current_situation.renigan_alive) {
    current_situation.WINNER = "sheriff";
    current_situation.is_end = true;
  }
}

Card GameManager::get_random_card() {
  Card miss_card, beer_card, gun_card, bang_card, card;
  miss_card = get_card("[MISS]");
  gun_card = get_card("[GUN]");
  beer_card = get_card("[BEER]");
  bang_card = get_card("[BANG]");
  int seed = std::rand() % 4;
  switch (seed) {
    case 0:card = miss_card;
      break;
    case 1:card = gun_card;
      break;
    case 2:card = beer_card;
      break;
    default:card = bang_card;
      break;
  }
  return card;
}

std::shared_ptr<PlayerInfo> GameManager::get_player(int player_id) {
  return current_situation.player_list[player_id];
}

Card GameManager::get_card(std::string name) const {
  Card card;
  card.name_card = std::move(name);
  return card;
}

void GameManager::drop_card(std::shared_ptr<PlayerInfo> player, std::string name) {
  Card card = get_card(std::move(name));
  player->cards_in_hand.erase(find(player->cards_in_hand.begin(), player->cards_in_hand.end(), card));
}

int GameManager::get_count_alive_players() const {
  int count = 0;
  for ( std::shared_ptr<PlayerInfo> player : current_situation.player_list )
    if (!(player->is_dead))
      count++;
  return count;
}

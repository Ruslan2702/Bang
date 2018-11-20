#include "GameSituation.h"
#include "GameManager.h"
#include <algorithm>
#include <map>

void GameManager::bang(PlayerInfo player_from, PlayerInfo &player_to) {
  if (can_bang(player_from, player_to)) {
    if (!(is_miss(player_to))) {
      player_to.HP--;
      if (player_to.HP == 0) {
        player_to.is_dead = true;
        std::string role = player_to.role;
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
      Card miss_card;
      miss_card.name_card = "[MISS]";
      player_to.cards_in_hand.erase(find(player_to.cards_in_hand.begin(), player_to.cards_in_hand.end(), miss_card));
    }
    check_end_game();
  }
}

bool GameManager::can_bang(PlayerInfo player_from, PlayerInfo &player_to) {
  return player_from.range + player_from.position >= player_to.position;
}

void GameManager::drink_beer(PlayerInfo &player) {
  if (player.MAX_HP > player.HP)
    player.HP++;
}

GameSituation GameManager::get_situation() {
  GameSituation dummy;
  return dummy; /// dummy
}

bool GameManager::is_miss(PlayerInfo player) {
  Card miss_card;
  miss_card.name_card = "[MISS]";
  return player.cards_in_hand.end() != find(player.cards_in_hand.begin(), player.cards_in_hand.end(), miss_card);
}

bool GameManager::check_count_cards(PlayerInfo player) {
  return player.HP >= player.cards_in_hand.size(); /// dummy
}

void GameManager::add_2_cards_before_move(PlayerInfo &player) {
  Card card_1 = get_random_card();
  Card card_2 = get_random_card();
  player.cards_in_hand.push_back(card_1);
  player.cards_in_hand.push_back(card_2);
}

void GameManager::gun(PlayerInfo &player) {
  player.range++;
  Card gun_card;
  gun_card.name_card = "[GUN]";
  player.cards_in_hand.erase(find(player.cards_in_hand.begin(), player.cards_in_hand.end(), gun_card));
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
  miss_card.name_card = "[MISS]";
  gun_card.name_card = "[GUN]";
  beer_card.name_card = "[BEER]";
  bang_card.name_card = "[BANG]";
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

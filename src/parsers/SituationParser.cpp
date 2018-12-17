#include "SituationParser.h"
#include "../../include/json.hpp"
#include "../logic/PlayerInfo.h"


GameSituation SituationParser::DecodeStep(std::string string_game) noexcept(false) {
  GameSituation game;

  json json_game = json::parse(string_game);

  for (int i = 0 ; i < 6; ++i) {
    std::shared_ptr<PlayerInfo> player(new PlayerInfo);
    std::string player_id = "player" + std::to_string(i);
    player->HP = json_game["player_list"][i][player_id]["hp"];
    player->name = json_game["player_list"][i][player_id]["name"];
    player->role = json_game["player_list"][i][player_id]["role"];
    player->range = json_game["player_list"][i][player_id]["range"];
    player->MAX_HP = json_game["player_list"][i][player_id]["max_hp"];
    player->position = json_game["player_list"][i][player_id]["position"];
    player->is_dead = json_game["player_list"][i][player_id]["is_dead"];


    json cards = json_game["player_list"][i][player_id]["cards_in_hand"];
    for (const std::string& element : cards[0]) {
      player->cards_in_hand.push_back({element, " "});
    }

    game.player_list.push_back(player);
  }

  game.is_end = json_game["is_end"];
  game.sherif_alive = json_game["sherif_alive"];
  game.renigan_alive = json_game["renigan_alive"];
  game.count_sherifs_helpers = json_game["count_sherifs_helpers"];
  game.count_bandits = json_game["count_bandits"];
  game.WINNER = json_game["winner"];

  return game;
}



std::string SituationParser::EncodeStep(GameSituation game) noexcept(false) {
  json player_list = json::array();
  for (int i = 0; i < 6; ++i) {
    json cards;
    for (auto card : game.player_list[i]->cards_in_hand) {
      cards.push_back(card.name_card);
    }

    json player = json::object({{"player" + std::to_string(i), {
        {"hp", game.player_list[i]->HP},
        {"name", game.player_list[i]->name},
        {"role", game.player_list[i]->role},
        {"range", game.player_list[i]->range},
        {"max_hp", game.player_list[i]->MAX_HP},
        {"position", game.player_list[i]->position},
        {"is_dead", game.player_list[i]->is_dead},
        {"cards_in_hand", json::array({cards})}}}});

    player_list.push_back(player);
  }

  json result = json::object({{"player_list", player_list},
                              {"is_end", game.is_end},
                              {"count_bandits", game.count_bandits},
                              {"sherif_alive", game.sherif_alive},
                              {"renigan_alive", game.renigan_alive},
                              {"count_sherifs_helpers", game.count_sherifs_helpers},
                              {"winner", game.WINNER}
                             });

  return result.dump();
}

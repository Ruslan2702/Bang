//
// Created by ruslan on 03.12.18.
//

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../../include/json.hpp"
#include "../logic/GameSituation.h"


using namespace nlohmann;

int main() {
  GameSituation game;
  std::shared_ptr<PlayerInfo> p1(new PlayerInfo);
  p1->HP = 3;
  p1->name = "BILL";
  p1->role = "BANDIT";
  p1->range = 5;
  p1->cards_in_hand.push_back({"BANG", " "});
  p1->cards_in_hand.push_back({"MISS", " "});
//  p1->cards_in_hand.emplace_back("BANG");
//  p1->cards_in_hand.emplace_back("MISS");
//  p1->cards_in_hand.emplace_back("BEER");
  game.player_list.push_back(p1);

//  std::shared_ptr<PlayerInfo> p2(new PlayerInfo);
//  p2->HP = 5;
//  p2->name = "TOM";
//  p2->role = "SHERIFF";
//  p2->range = 2;
//  p2->cards_in_hand.push_back({"BEER", " "});
////  p2->cards_in_hand.emplace_back("MISS");
////  p2->cards_in_hand.emplace_back("BEER");
////  p2->cards_in_hand.emplace_back("BEER");
//  game.player_list.push_back(p2);




  json player_list = json::array();
  for (int i = 0; i < 1; ++i) {
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
  std::cout << player_list.dump() << std::endl;
  std::string npl = player_list.dump();
  std::cout << npl << std::endl;
  json back = json::parse(npl);
  std::cout << back[0] << std::endl;

  json result = json::object({{"player_list", player_list},
                              {"is_end", game.is_end},
                              {"count_bandits", game.count_bandits},
                              {"sherif_alive", game.sherif_alive},
                              {"renigan_alive", game.renigan_alive},
                              {"count_sherifs_helpers", game.count_sherifs_helpers},
                              {"winner", game.WINNER}
                              });
//  std::cout << result.dump() << std::endl;


//  std::cout << player_list[0].dump() << std::endl;
//
//  std::cout << result["player_list"][0]["player0"]["hp"] << std::endl;
//
//
  GameSituation newGame;
  std::shared_ptr<PlayerInfo> np1(new PlayerInfo);
  np1->HP = result["player_list"][0]["player0"]["hp"];
  np1->name = player_list[0]["player0"]["name"];
  np1->role = player_list[0]["player0"]["role"];
  np1->range = player_list[0]["player0"]["range"];
  json cards = player_list[0]["player0"]["cards_in_hand"];
//  std::cout << cards[0].dump() << std::endl;
  for (const std::string& element : cards[0]) {
    np1->cards_in_hand.push_back({element, " "});
  }
//  np1->cards_in_hand.push_back({"BANG", " "});
//  np1->cards_in_hand.push_back({"MISS", " "});
  newGame.player_list.push_back(np1);

  assert(game.player_list[0]->HP == newGame.player_list[0]->HP);
  assert(game.player_list[0]->name == newGame.player_list[0]->name);
  assert(game.player_list[0]->role == newGame.player_list[0]->role);
  assert(game.player_list[0]->range == newGame.player_list[0]->range);










//  std::cout << t.dump() << std::endl;
//  std::cout << t2.dump() << std::endl;
//  std::cout << "Hello, world!" << std::endl;
//  json j1 = {{"is_end", game.is_end},
//             {"count_bandits", game.count_bandits},
//             {"sherif_alive", game.sherif_alive},
//             {"player_list", json::array({
//                                             json::object({{"player 1",{
//                                                 {"hp", game.player_list[0]->HP},
//                                                 {"name", game.player_list[0]->name},
//                                                 {"cards_in_hand", json::array({game.player_list[0]->cards_in_hand})}
//                                             }
//                                                           }}),
//                                             json::object({{"player 2", {
//                                                 {"hp", 15},
//                                                 {"name", "kate"},
//                                                 {"cards_in_hand", json::array({"miss", "bang"})}}
//                                                           }})
//                                         })}};
//  json j2 = j1;
//  std::cout << std::setw(4) << j1 << std::endl;
//
//  j2["player_list"][0]["player 1"]["cards_in_hand"].push_back("another one");
//  j2["player_list"][0]["player 1"]["cards_in_hand"].push_back("bites the dust!");
//  j2["player_list"].push_back({{"player 3", {{"hp", 9999},
//                                             {"name", "xXGODGAMERXx"},
//                                             {"cards_in_hand", json::array({"gg", "ez"})}}
//                               }});
//  std::cout << std::setw(4) << j2 << std::endl;
  return 0;
}



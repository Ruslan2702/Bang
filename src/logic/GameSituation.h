//
// Created by Андрей on 07.11.18.
//

#ifndef BANG_GAMESITUATION_H
#define BANG_GAMESITUATION_H

#include <vector>

class GameSituation {
public:
    std::vector<std::string> cards_in_hand;
//    InfoAboutPlayes info;
//    Player* current_player;
//    Move last_move;
    bool is_end;
    int game_id;
//    CardsFrontPlayes cards_fromt_player;
};


#endif //BANG_GAMESITUATION_H

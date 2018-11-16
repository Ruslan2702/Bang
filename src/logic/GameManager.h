#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>
#include "GameSituation.h"

class GameManager {
public:
    void bang(int from_player, int to_player);
    bool can_bang(int from_player, int to_player); /// расчет ренджи
    void drink_beer(int player_id); /// пиво на себя полюбому
    bool is_miss(int id_player);
    GameSituation get_situation();
    bool check_count_cards(int player_id); /// карт должно быть столько, сколько HP
    void add_2_cards_before_move(int player_id); /// добавление 2 карт перед началом хода
    void gun(int id_player); /// + 1 к радиуму поражения

    GameSituation current_situation;
};

#endif //GAME_MANAGER_GAMEMANAGER_H

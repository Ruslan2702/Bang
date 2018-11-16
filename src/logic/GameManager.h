#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>
#include "GameSituation.h"

class GameManager {
public:
    void bang(int from_player, int to_player);
    bool can_bang(int from_player, int to_player); /// расчет ренджи
    void drink_beer(int player_id); /// пиво на себя полюбому
    bool is_miss();
    GameSituation get_situation();

    GameSituation current_situation;
};

#endif //GAME_MANAGER_GAMEMANAGER_H

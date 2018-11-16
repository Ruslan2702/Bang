#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>

class GameManager {
public:
    void bang(int from_player, int to_player, GameSituation& situation);
    bool can_bang(int from_player, int to_player, GameSituation& situation); /// расчет ренджи
    void drink_beer(int player_id, GameSituation& situation); /// пиво на себя полюбому
    bool is_miss();
    GameSituation get_situation();

    GameSituation current_situation;
};

#endif //GAME_MANAGER_GAMEMANAGER_H

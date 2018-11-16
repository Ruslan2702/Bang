#include "GameSituation.h
#include "GameManager.h"

void GameManager::bang(int from_player, int to_player, GameSituation &situation) {
    return;
}

bool GameManager::can_bang(int from_player, int to_player, GameSituation &situation) {
    return true; /// dummy
}

void GameManager::drink_beer(int player_id, GameSituation &situation) {
    return;
}

GameSituation GameManager::get_situation() {
    GameSituation dummy;
    return dummy;
}

bool GameManager::is_miss() {
    return false;
}


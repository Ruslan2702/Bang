#ifndef GAME_MANAGER_GAMEMANAGER_H
#define GAME_MANAGER_GAMEMANAGER_H

#include <iostream>
#define COUNT_CARDS_IN_HAND 6
struct cards {
    std::vector<int>*role;
    std::vector<int>*card;
};

class GameManager {
private:
    /*          */
public:
    cards* get_cards() {}
    cards* create_start_game_situation() {}
    cards* change_game_situation(cards* GameStep) {}
    cards* take_users_situation(cards* user) {}
protected:
    /*          */
};

#endif //GAME_MANAGER_GAMEMANAGER_H

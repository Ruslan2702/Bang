#include "GameManager.h"

cards* get_cards() {
    cards *tmpCards = new cards[COUNT_CARDS_IN_HAND];
    return tmpCards;
}
cards* create_start_game_situation() {
    cards *tmpCards = new cards[COUNT_CARDS_IN_HAND];
    return tmpCards;
}
cards* change_game_situation(cards* GameStep) {
    return GameStep;
}
cards* take_users_situation(cards* user) {
    return user;
}
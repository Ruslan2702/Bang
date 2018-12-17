#ifndef GAME_LOGIC_CARDSPARSER_H
#define GAME_LOGIC_CARDSPARSER_H

#include <iostream>
#include <map>
#include <string>
#include "../logic/Card.h"
#include <vector>

class GetCardsInterface {
public:
    virtual ~GetCardsInterface() = default;

    virtual std::vector<Card> GetCardsDec() = 0;
};


class CardParserTxt : public GetCardsInterface {
public:
    CardParserTxt() = default;
    ~CardParserTxt() = default;

     std::vector<Card> GetCardsDec();
};

class CardParserConst : public GetCardsInterface {
public:
    CardParserConst() = default;
    ~CardParserConst() = default;

    std::vector<Card> GetCardsDec();

private:
    int count_card = 90;
    int count_miss = 20;
    int count_beer = 10;
    int count_bang = 60;
};


#endif //GAME_LOGIC_CARDSPARSER_H

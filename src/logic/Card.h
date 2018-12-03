//
// Created by Андрей on 07.11.18.
//

#ifndef BANG_CARD_H
#define BANG_CARD_H

#include <iostream>

struct Card {
  std::string name_card;
  std::string description;
  bool operator==(const Card &right) const {
    return name_card == right.name_card;
  }
};

#endif //BANG_CARD_H

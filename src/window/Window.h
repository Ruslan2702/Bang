//
// Created by ruslan on 14.11.18.
//

#ifndef BANG_WINDOW_H
#define BANG_WINDOW_H


#include <ncurses.h>
#include "../logic/GameSituation.h"

class Window {
 public:
  Window();
  ~Window();
  void HelloMessage(std::string& host, int* port);
  void YouAreConnected();
  void GameInfoMessage();
  void UpgradeWindowByNewStep();
  std::string YourTurn();


private:
  void GetAddress(std::string& host, int* port);
  std::string CardKeyboard();
  std::string ActionKeyboard(std::string selectedCard);
  std::string PlayerKeyboard(std::string selectedCard, std::string selectedAction);
  int PrintKeyboardAndGetChoise(const std::vector<std::string>& items, const std::string& msg);

  int rows;
  int cols;
  GameSituation gameSituation;
};




#endif //BANG_WINDOW_H

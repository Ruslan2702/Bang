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
  void StartGameMessage();
  void UpgradeWindowByNewStep();


private:
  void GetAddress(std::string& host, int* port);

  int rows;
  int cols;
  GameSituation gameSituation;
};




#endif //BANG_WINDOW_H

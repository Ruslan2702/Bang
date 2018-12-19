//
// Created by ruslan on 14.11.18.
//

#include <iostream>
#include "Window.h"
#include <string>
#include <fstream>
#include <unistd.h>
#include <vector>


#define msleep(msec) usleep(msec*1000)

const int LABEL_LENGTH = 31;

Window::Window() {
    initscr();

    int nRow = 0;
    int nCol = 0;

    getmaxyx(stdscr, nRow, nCol);
    this->rows = nRow;
    this->cols = nCol;
}

Window::~Window() {
    getch();
    endwin();
}

void Window::HelloMessage(std::string& host, int* port) {
    if (rows < 20 || cols < 40) {
        printw("Please, stretch the terminal window and try again.");
        throw std::runtime_error("Too small terminal window");
    }

    std::ifstream fin("src/window/hello_message.txt");
    std::string buff;

    int currentRow = 0;
    int mid = (cols - LABEL_LENGTH) / 2;
    while (getline(fin, buff)) {
        currentRow++;
        mvwprintw(stdscr, currentRow, mid, "%s", buff.c_str());
    }

    mvwprintw(stdscr, this->rows - 1, 0, "Press Ctr+C to exit");
    mvwprintw(stdscr, currentRow + 5, 0, "Enter server address to connect to the game (ex.: 127.0.0.1 5555)\n");
    scanw("%s %d", host.c_str(), port);

    fin.close();
}

void Window::YouAreConnected(char playersNum, char myID) {
    currentPlayer = 0;
    id = myID;

    sheriff = 3;
    std::string out = "\nNow here are " + std::to_string(playersNum) + "/6 players. Please wait";
    printw(out.c_str());
    refresh();
    msleep(2000);
}

void Window::GameInfoMessage() {
    for (int i = 0; i < gameSituation.player_list.size(); ++i) {
      if (gameSituation.player_list[i]->role == "SHERIFF") {
        sheriff = i;
        break;
      }
    }

    clear();
    mvwprintw(stdscr, 0, 0, "GameID: 1442\n\n");

    for (int i = 0; i < gameSituation.player_list.size(); i++) {
      if (i == id) {
        continue;
      }

      if (i == currentPlayer) {
        addch('*');
      }
      else {
        addch(' ');
      }

      printw(" %dHP   %s", gameSituation.player_list[i]->HP, gameSituation.player_list[i]->name.c_str());

      if (i == sheriff) {
        printw("  (SHERIFF)");
      }

      printw("\n");
    }

    printw("\n\nLast step:\n JOHN: 'BANG' ->  Player2");

    mvwprintw(stdscr, 1, cols / 2, "YOU:");
    mvwprintw(stdscr, 2, cols / 2 + 3, "#NAME: %s", gameSituation.player_list[id]->name.c_str());
    mvwprintw(stdscr, 3, cols / 2 + 3, "#HP: %d", gameSituation.player_list[id]->HP);
    mvwprintw(stdscr, 4, cols / 2 + 3, "#ROLE: %s", gameSituation.player_list[id]->role.c_str());
    mvwprintw(stdscr, 5, cols / 2 + 3, "#RANGE: %d", gameSituation.player_list[id]->range);

    mvwprintw(stdscr, 6, cols / 2 + 3, "#CARDS:");
    for (int i = 0; i < gameSituation.player_list[id]->cards_in_hand.size(); ++i) {
      mvwprintw(stdscr, 7 + i, cols / 2 + 6, "%s", gameSituation.player_list[id]->cards_in_hand[i].name_card.c_str());
    }
    printw("\n\n\n\n");
    refresh();
}

void Window::UpgradeWindowByNewStep(const GameSituation& newGame) {
  gameSituation = newGame;
  GameInfoMessage();
  printw("Last step:\n : 'BANG' ->  Player2");
  refresh();
  msleep(2000);
}

std::string Window::YourTurn() {
  std::string card = CardKeyboard();
  std::string action = ActionKeyboard(card);
  std::string toPlayer;
  if (action == "USE") {
    toPlayer = PlayerKeyboard(card, action);
    GameInfoMessage();
    printw("Your step:\n '%s' ->  %s", card.c_str(), toPlayer.c_str());
    std::string result = "<STEP> " + action + ' ' + card + ' ' + toPlayer + " </STEP>";
    return result;
  }

  GameInfoMessage();
  printw("Your step:\n DROP '%s'", card.c_str());
  std::string result = "<STEP> " + action + ' ' + card + " </STEP>";
  return result;
}

std::string Window::CardKeyboard() {
  std::vector<std::string> cards;
  for (const auto& card_struct : gameSituation.player_list[id]->cards_in_hand) {
    cards.emplace_back(card_struct.name_card);
  }

  std::string msg = "Your turn! Select a card";
  return gameSituation.player_list[id]->cards_in_hand[
      PrintKeyboardAndGetChoise(cards, msg)
      ].name_card;
}

std::string Window::ActionKeyboard(std::string selectedCard) {
  std::vector<std::string> items{"DROP", "USE"};
  std::string msg = "Selected card: " + selectedCard + '\n';
  return items[PrintKeyboardAndGetChoise(items, msg)];
}

std::string Window::PlayerKeyboard(std::string selectedCard, std::string selectedAction) {
  std::vector<std::string> players;
  for (int i = 0; i < gameSituation.player_list.size(); ++i) {
    if (i == id) {
      continue;
    }

    players.emplace_back(gameSituation.player_list[i]->name);
  }

  std::string msg = "Selected card: " + selectedCard + '\n' +
      "Selected action: " + selectedAction + '\n';
  return players[PrintKeyboardAndGetChoise(players, msg)];
}

int Window::PrintKeyboardAndGetChoise(const std::vector<std::string> &items,
                                      const std::string& msg) {
  curs_set(0);
  keypad(stdscr, true);
  unsigned int choice = 0;

  while (true) {
    clear();
    GameInfoMessage();
    printw("%s\n", msg.c_str());
    for (int i = 0; i < items.size(); i++) {
      if ( i == choice ) 
        addch('>'); 
      else
        addch(' '); 

      printw("%s\n", items[i].c_str());
    }

    switch (getch()) {
      case KEY_UP:
        if (choice) 
          choice--;
        break;
      case KEY_DOWN:
        if (choice != items.size() - 1) 
          choice++;
        break;
      case 10:
        return choice;
    }
  }
}

Window &Window::getInstance() {
  static Window instance;
  return instance;
}

bool Window::GameOver() {
  return gameSituation.is_end;
}

bool Window::YourStepTime() {
  return currentPlayer == id;
}

void Window::EndMessage() {
  printw("THE GAME IS OVER!");
}


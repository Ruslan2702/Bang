//
// Created by ruslan on 14.11.18.
//

#include <iostream>
#include "Window.h"
#include <string>
#include <fstream>
#include <unistd.h>


#define msleep(msec) usleep(msec*1000)

const int LABEL_LENGTH = 31;

Window::Window() {
    initscr();
//    WINDOW* win = newwin(30, 50, 0, 0);


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

void Window::YouAreConnected() {
    printw("\n\nNow here are 3/6 players. Please wait");
    refresh();
    msleep(2000);
}

void Window::GameInfoMessage() {
    clear();
    mvwprintw(stdscr, 0, 0, "GameID: 1442\n\n");
    printw("Your name: Joe\n");
    printw("Your role: Sheriff\n");
    printw("Your health: 4\n");
    printw("Your gun power: 1\n\n\n\n");
    refresh();
//    msleep(2000);
}

void Window::UpgradeWindowByNewStep() {
  GameInfoMessage();
  printw("Last step:\n Player1: 'BANG' ->  Player2");
  refresh();
  msleep(2000);
}

std::string Window::YourTurn() {
  std::string card = CardKeyboard();
  std::string action = ActionKeyboard(card);
  std::string toPlayer;
  if (action == "Use") {
    toPlayer = PlayerKeyboard(card, action);
    GameInfoMessage();
    printw("Your step:\n '%s' ->  %s", card.c_str(), toPlayer.c_str());
    return action + card + toPlayer;
  }

  GameInfoMessage();
  printw("Your step:\n DROP '%s'", card.c_str());
  return "Goog";
}

std::string Window::CardKeyboard() {
  std::vector<std::string> items{"Bang", "Beer", "Miss"};
  std::string msg = "Your turn! Select an action\n";
  return items[PrintKeyboardAndGetChoise(items, msg)];
}

std::string Window::ActionKeyboard(std::string selectedCard) {
  std::vector<std::string> items{"Drop", "Use"};
  std::string msg = "Selected card: " + selectedCard + '\n';
  return items[PrintKeyboardAndGetChoise(items, msg)];
}

std::string Window::PlayerKeyboard(std::string selectedCard, std::string selectedAction) {
  std::vector<std::string> items{"Player 1", "Player 2", "Player 4", "Player 5", "Player 6",};
  std::string msg = "Selected card: " + selectedCard + '\n' +
      "Selected action: " + selectedAction + '\n';
  return items[PrintKeyboardAndGetChoise(items, msg)];
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
      if ( i == choice ) //Если текущий элемент совпадает с выбором пользователя
        addch('>'); //Выводим указатель
      else
        addch(' '); //Иначе выводим " ", для равновесия

      printw("%s\n", items[i].c_str());
    }

    switch (getch()) {
      case KEY_UP:
        if (choice) //Если возможно, переводим указатель вверх
          choice--;
        break;
      case KEY_DOWN:
        if (choice != 3) //Если возможно, переводим указатель вниз
          choice++;
        break;
      case 10:
//        printw("\nYour choise is: %s", items[choice].c_str());
//        refresh();
//        msleep(2000);
        return choice;
    }
  }
}






//int main(int argc, char* argv[]) {
//    Window window;
//
//    std::string host = "";
//    int port = 0;
//
//    try {
//        window.HelloMessage(host, &port);
//    } catch (...) {}
//
//
//
//    return 0;
//}
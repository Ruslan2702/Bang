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

    mvwprintw(stdscr, currentRow + 5, 0, "Enter server address to connect to the game (ex.: 127.0.0.1 5555)\n");
    scanw("%s %d", host.c_str(), port);

    fin.close();
}

void Window::YouAreConnected() {
    printw("\n\nNow here are 3/6 players. Please wait");
    refresh();
    msleep(2000);
}

void Window::StartGameMessage() {
    msleep(2000);
    clear();
    mvwprintw(stdscr, 0, 0, "GameID: 1442\n\n");
    printw("Your name: Joe\n");
    printw("Your role: Sheriff\n");
    printw("Your health: 4\n\n");

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
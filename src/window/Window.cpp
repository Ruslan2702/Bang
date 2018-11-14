//
// Created by ruslan on 14.11.18.
//

#include <iostream>
#include "Window.h"
#include <string>
#include <fstream>

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

    std::ifstream fin("hello_message.txt");
    std::string buff;

    int currentRow = 0;
    int mid = (cols - LABEL_LENGTH) / 2;
    while (getline(fin, buff)) {
        currentRow++;
        mvwprintw(stdscr, currentRow, mid, "%s", buff.c_str());
    }

    mvwprintw(stdscr, currentRow + 5, 0, "Enter server address to connect to the game (127.0.0.1 5555)\n");
    scanw("%s %d", host.c_str(), port);

    printw("\nhost: %s, port: %d", host.c_str(), *port);

    fin.close();
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
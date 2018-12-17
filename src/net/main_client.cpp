//
// Created by ruslan on 10.11.18.
//

// Паттерн "Команда"
// Фабрика, которая создает пул серилизаторов
// Observer
// Посетитель


#include <iostream>
#include "Client.h"
#include "../window/Window.h"
#include <fstream>
#include "../logic/GameSituation.h"
#include "../parsers/SituationParser.h"


int main(int argv, char** argc) {
    SituationParser parser;

//    std::string result = parser.EncodeStep(game);
//    const char* answer = R"({"count_bandits":2,"count_sherifs_helpers":3,"is_end":false,"player_list":[{"player0":{"cards_in_hand":[null],"hp":4,"is_dead":false,"max_hp":0,"name":"BOB","position":0,"range":1,"role":""}},{"player1":{"cards_in_hand":[null],"hp":2,"is_dead":false,"max_hp":0,"name":"ANN","position":0,"range":1,"role":""}},{"player2":{"cards_in_hand":[null],"hp":3,"is_dead":false,"max_hp":0,"name":"KATE","position":0,"range":1,"role":""}},{"player3":{"cards_in_hand":[null],"hp":1,"is_dead":false,"max_hp":0,"name":"TOM","position":0,"range":1,"role":""}},{"player4":{"cards_in_hand":[null],"hp":4,"is_dead":false,"max_hp":0,"name":"JOHN","position":0,"range":1,"role":""}},{"player5":{"cards_in_hand":[["[BANG]","[MISS]","[MISS]","[BEER]"]],"hp":3,"is_dead":false,"max_hp":0,"name":"BILL","position":0,"range":5,"role":"BANDIT"}}],"renigan_alive":true,"sherif_alive":true,"winner":""})";
//    std::string json_answer(answer);
//    const GameSituation& newGame = parser.DecodeStep(json_answer);

    Window& window = Window::getInstance();

    std::string host;
    int port = 0;
    window.HelloMessage(host, &port);

    Client& client = Client::getInstance(host.c_str(), port);

    client.JoinTheGame();
    char myID = 0;
    char playersNum = 0;
    client.GetFirstMessage(&playersNum, &myID);
    window.YouAreConnected(playersNum, myID);

    std::string gameSit = client.GetGameSituation();
    const GameSituation& newGame = parser.DecodeStep(gameSit);
    window.UpgradeWindowByNewStep(newGame);
    window.GameInfoMessage();

    while (!window.GameOver()) {
        if (window.YourStepTime()) {
            client.SendNewStep(window.YourTurn());
            window.currentPlayer++;
            continue;
        }

        std::string gameSit = client.GetGameSituation();
        const GameSituation& newGame = parser.DecodeStep(gameSit);
        window.UpgradeWindowByNewStep(newGame);
        window.GameInfoMessage();
        window.currentPlayer++;
    }

    window.EndMessage();
    return 0;
}
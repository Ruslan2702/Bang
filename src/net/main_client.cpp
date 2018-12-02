//
// Created by ruslan on 10.11.18.
//

#include <iostream>
#include "Client.h"
#include "../window/Window.h"
#include <fstream>
#include "../logic/GameSituation.h"


int main(int argv, char** argc) {
//    std::cout << "Client started!" << std::endl;
    GameSituation game;
    game.is_end = false;
    game.is_sherif = true;
    game.is_renigan = true;
    game.count_bandits = 2;
    game.count_sherifs_helpers = 3;

    std::shared_ptr<PlayerInfo> p1(new PlayerInfo);
    p1->HP = 4;
    p1->name = "BOB";

    std::shared_ptr<PlayerInfo> p2(new PlayerInfo);
    p2->HP = 2;
    p2->name = "ANN";

    std::shared_ptr<PlayerInfo> p3(new PlayerInfo);
    p3->HP = 3;
    p3->name = "KATE";

    std::shared_ptr<PlayerInfo> p4(new PlayerInfo);
    p4->HP = 1;
    p4->name = "TOM";

    std::shared_ptr<PlayerInfo> p5(new PlayerInfo);
    p5->HP = 4;
    p5->name = "JOHN";

    std::shared_ptr<PlayerInfo> p6(new PlayerInfo);
    p6->HP = 3;
    p6->name = "BILL";
    p6->role = "BANDIT";
    p6->range = 5;
    p6->cards_in_hand.emplace_back("BANG");
    p6->cards_in_hand.emplace_back("BANG");
    p6->cards_in_hand.emplace_back("MISS");
    p6->cards_in_hand.emplace_back("BEER");

    game.player_list.push_back(p1);
    game.player_list.push_back(p2);
    game.player_list.push_back(p3);
    game.player_list.push_back(p4);
    game.player_list.push_back(p5);
    game.player_list.push_back(p6);



    Window& window = Window::getInstance();
    std::string host;
    int port = 0;
    window.HelloMessage(host, &port);

    int myId = 3; // Получен от сервера

//    Client client(host.c_str(), port);


//    client.JoinTheGame();
    window.YouAreConnected(game);
//    client.SendNewStep("First step in this game");
    window.GameInfoMessage();
//    window.UpgradeWindowByNewStep();
    window.YourTurn();
//    std::cout << client.GetGameSituation() << std::endl;
//    std::cout << "Client works!" << std::endl;

    return 0;
}
//
// Created by Андрей on 18.12.18.
//


#include <iostream>
#include <stdexcept>
#include <thread>
#include "Server.h"
#include <vector>
#include "../parsers/SituationParser.h"
#include "../parsers/StepParser.h"
#include "../BD/DataBaseManager.h"

GameSituation get_start_situation() {
    GameSituation situation;
    Card card;
    card.name_card = "BANG";

    std::shared_ptr<PlayerInfo> player1(new  PlayerInfo);
    player1->name = "A";
    player1->role = "bandit";
    player1->cards_in_hand.push_back(card);
    player1->position = 0;
    player1->HP = 5;
    player1->MAX_HP = 5;
    std::shared_ptr<PlayerInfo> player2(new  PlayerInfo);
    player2->name = "B";
    player2->role = "bandit";
    player2->cards_in_hand.push_back(card);
    player2->position = 1;
    player2->HP = 5;
    player2->MAX_HP = 5;
    std::shared_ptr<PlayerInfo> player3(new  PlayerInfo);
    player3->name = "C";
    player3->role = "bandit";
    player3->cards_in_hand.push_back(card);
    player3->position = 2;
    player3->HP = 5;
    player3->MAX_HP = 5;
    std::shared_ptr<PlayerInfo> player4(new  PlayerInfo);
    player4->name = "D";
    player4->role = "helper";
    player4->cards_in_hand.push_back(card);
    player4->position = 3;
    player4->HP = 5;
    player4->MAX_HP = 5;
    std::shared_ptr<PlayerInfo> player5(new  PlayerInfo);
    player5->name = "E";
    player5->role = "sheriff";
    player5->cards_in_hand.push_back(card);
    player5->position = 4;
    player5->HP = 5;
    player5->MAX_HP = 5;
    std::shared_ptr<PlayerInfo> player6(new  PlayerInfo);
    player6->name = "F";
    player6->role = "rinnegan";
    player6->cards_in_hand.push_back(card);
    player6->position = 5;
    player6->HP = 5;
    player6->MAX_HP = 5;

    situation.player_list.push_back(player1);
    situation.player_list.push_back(player2);
    situation.player_list.push_back(player3);
    situation.player_list.push_back(player4);
    situation.player_list.push_back(player5);
    situation.player_list.push_back(player6);

    return situation;
}

int main(int argc, char *argv[]) /// запуск сервера
{
    try
    {
        int MAX_CONNECT = 2;
        int TIME_TO_MOVE_SEC = 30;
        int TIME_TO_MOVE_MSEC = 0;

        GameManager gameManager;

        Server server("5555", MAX_CONNECT);

        DataBaseManager dataBaseManager;
        dataBaseManager.CreateTable();

        SituationParser situationParser;
        GameSituation situation = get_start_situation();
        std::string start_situation = situationParser.EncodeStep(situation);

        server.get_players(MAX_CONNECT);
        std::cout << "THERE ARE " << MAX_CONNECT << " CON" << std::endl;
        GameSituation current_sitution;

        server.send_hellow_msg();
        server.send_current_situation(start_situation);

        int game_move = 0;
        std::string WINNER;
        while(WINNER == "")
        {
//            std::string step = server.get_step(game_move % MAX_CONNECT);
//            Step valid_step; /// dummy
//            WINNER = server.upgrade_situation(valid_step, gameManager, current_sitution);
//
//            server.send_everybode_step(step);
//            server.send_current_situation(current_sitution);
//            server.insert_step_in_db(step);
//
//            ++game_move;
        }

        server.send_end_msg(WINNER);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
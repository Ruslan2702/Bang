//
// Created by Андрей on 16.11.18.
//

#include <gtest/gtest.h>
#include "../GameSituation.h"
#include "../GameManager.h"

GameSituation get_fake_situation() {
    GameSituation fake_situation;

    std::shared_ptr<PlayerInfo> player1;
    player1->HP = 3;
    player1->role = "bandit";

    std::shared_ptr<PlayerInfo> player2;
    player2->HP = 3;
    player2->role = "bandit";

    std::shared_ptr<PlayerInfo> player3;
    player3->HP = 3;
    player3->role = "bandit";

    std::shared_ptr<PlayerInfo> player4;
    player4->HP = 3;
    player4->role = "helper";

    std::shared_ptr<PlayerInfo> player5;
    player5->HP = 3;
    player5->role = "sheriff";

    std::shared_ptr<PlayerInfo> player6;
    player6->HP = 3;
    player6->role = "rinnegan";

    fake_situation.player_list;

    fake_situation.player_list.push_back(player1);
    fake_situation.player_list.push_back(player2);
    fake_situation.player_list.push_back(player3);
    fake_situation.player_list.push_back(player4);
    fake_situation.player_list.push_back(player5);
    fake_situation.player_list.push_back(player6);

    return fake_situation;
};

class TestGameSituation : public ::testing::Test {
    virtual void SetUp() {
        manager.current_situation = get_fake_situation();
    }

public:
    GameManager manager;
};

TEST_F(TestGameSituation, simple_beer_01) {
    int from_player = 0;

    int before_HP = manager.current_situation.player_list[from_player]->HP;
    manager.drink_beer(from_player, );
}



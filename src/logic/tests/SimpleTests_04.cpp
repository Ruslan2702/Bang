//
// Created by Андрей on 16.11.18.
//

#include <gtest/gtest.h>
#include "../GameSituation.h"
#include "../GameManager.h"
//#include "../PlayerInfo.h"
#include <iostream>

GameSituation get_fake_situation() {
    GameSituation fake_situation;



    std::shared_ptr<PlayerInfo> player1;
    player1->HP = 3;
    player1->role = "bandit";
    player1->name = "Bob";


    std::shared_ptr<PlayerInfo> player2;
    player2->HP = 3;
    player2->role = "bandit";
    player2->name = "Tom";

    std::shared_ptr<PlayerInfo> player3;
    player3->HP = 3;
    player3->role = "bandit";
    player3->name = "Rob";

    std::shared_ptr<PlayerInfo> player4;
    player4->HP = 3;
    player4->role = "helper";
    player4->name = "Joe";

    std::shared_ptr<PlayerInfo> player5;
    player5->HP = 3;
    player5->role = "sheriff";
    player5->name = "Li";

    std::shared_ptr<PlayerInfo> player6;
    player6->HP = 3;
    player6->role = "rinnegan";
    player6->name = "Loo";

    fake_situation.player_list.push_back(player1);
    fake_situation.player_list.push_back(player2);
    fake_situation.player_list.push_back(player3);
    fake_situation.player_list.push_back(player4);
    fake_situation.player_list.push_back(player5);
    fake_situation.player_list.push_back(player6);

    return fake_situation;
}

class TestGameSituation : public ::testing::Test {
    virtual void SetUp() {
        manager.current_situation = get_fake_situation();
    }

public:
    GameManager manager;
};

TEST_F(TestGameSituation, simple_beer_01) {
    /// simple beer
    int from_player = 0;

    GameManager manager;
    manager.current_situation = get_fake_situation();

    int before_HP = manager.current_situation.player_list[from_player]->HP;

    manager.drink_beer(from_player);

    int after_HP = manager.current_situation.player_list[from_player]->HP;

    EXPECT_EQ(before_HP + 1, after_HP);
}

TEST_F(TestGameSituation, simple_beer_02) {
    /// limit beer + 1 not work
    int from_player = 0;

    GameManager manager;
    manager.current_situation = get_fake_situation();

    int before_HP = ++manager.current_situation.player_list[from_player]->HP;

    manager.drink_beer(from_player);

    int after_HP = manager.current_situation.player_list[from_player]->HP;

    EXPECT_EQ(before_HP, after_HP);
}

TEST_F(TestGameSituation, simple_bang_can_bang_01) {
    /// simple can_bang true
    int from_player = 0;
    int to_player = 1;

    manager.current_situation.player_list[from_player]->range = 1;
    EXPECT_TRUE(manager.can_bang(from_player, to_player));
}

TEST_F(TestGameSituation, simple_bang_can_bang_02) {
    /// simple can_bang false
    int from_player = 0;
    int to_player = 2;

    manager.current_situation.player_list[from_player]->range = 1;
    EXPECT_FALSE(manager.can_bang(from_player, to_player));
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


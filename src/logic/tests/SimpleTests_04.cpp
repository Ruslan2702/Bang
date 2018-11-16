//
// Created by Андрей on 16.11.18.
//

#include <gtest/gtest.h>
#include "../GameSituation.h"
#include "../GameManager.h"
#include "../PlayerInfo.h"
#include <iostream>

GameSituation get_fake_situation() {

    /// ПОЧЕМУ В ТАКОМ СЛУЧАЕ ERROR 11?
    ///std::shared_ptr<PlayerInfo> player2;
    ///(*player2).HP = 3;
    ///std::cout << (*player2).HP << std::endl;
    ///player2->role = "bandit";
    ///player2->name = "Tom";

    GameSituation fake_situation;

    std::shared_ptr<PlayerInfo> player1 = std::make_shared<PlayerInfo>();
    (*player1).HP = 3;
    (*player1).role = "bandit";
    (*player1).name = "Bob";
    (*player1).MAX_XP = 3;

    std::shared_ptr<PlayerInfo> player2 = std::make_shared<PlayerInfo>();
    (*player2).HP = 3;
    (*player2).role = "bandit";
    (*player2).name = "Tom";
    (*player2).MAX_XP = 3;

    std::shared_ptr<PlayerInfo> player3 = std::make_shared<PlayerInfo>();
    (*player3).HP = 3;
    (*player3).role = "bandit";
    (*player3).name = "Rob";
    (*player3).MAX_XP = 3;

    std::shared_ptr<PlayerInfo> player4 = std::make_shared<PlayerInfo>();
    (*player4).HP = 3;
    (*player4).role = "helper";
    (*player4).name = "Joe";
    (*player4).MAX_XP = 3;

    std::shared_ptr<PlayerInfo> player5 = std::make_shared<PlayerInfo>();
    (*player5).HP = 3;
    (*player5).role = "sheriff";
    (*player5).name = "Li";
    (*player5).MAX_XP = 3;

    std::shared_ptr<PlayerInfo> player6 = std::make_shared<PlayerInfo>();
    (*player6).HP = 3;
    (*player6).role = "rinnegan";
    (*player6).name = "Loo";
    (*player6).MAX_XP = 3;

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

TEST_F(TestGameSituation, simple_beer_01) noexcept(false) {
    /// simple beer +1 HP
    int from_player = 0;

    (*manager.current_situation.player_list[from_player]).HP = 3;
    (*manager.current_situation.player_list[from_player]).HP = 4;

    int before_HP = manager.current_situation.player_list[from_player]->HP;

    manager.drink_beer(from_player);

    int after_HP = manager.current_situation.player_list[from_player]->HP;

    EXPECT_EQ(before_HP + 1, after_HP);
}

TEST_F(TestGameSituation, simple_beer_02) noexcept(false) {
    /// limit HP + 1 not work
    int from_player = 0;

    (*manager.current_situation.player_list[from_player]).HP = 3;
    (*manager.current_situation.player_list[from_player]).HP = 3;

    int before_HP = manager.current_situation.player_list[from_player]->HP;

    manager.drink_beer(from_player);

    int after_HP = manager.current_situation.player_list[from_player]->HP;

    EXPECT_EQ(before_HP, after_HP);
}

TEST_F(TestGameSituation, simple_bang_can_bang_01) noexcept(false) {
    /// simple can_bang true
    int from_player = 0;
    int to_player = 1;

    (*manager.current_situation.player_list[from_player]).range = 1;
    EXPECT_TRUE(manager.can_bang(from_player, to_player));
}

TEST_F(TestGameSituation, simple_bang_can_bang_02) noexcept(false) {
    /// simple can_bang false
    int from_player = 0;
    int to_player = 2;

    (*manager.current_situation.player_list[from_player]).range = 1;
    EXPECT_FALSE(manager.can_bang(from_player, to_player));
}

TEST_F(TestGameSituation, simple_is_miss_01) {
    /// have MISS card
    Card miss_card;
    miss_card.name_card = "[MISS]";

    int id_player = 0;
    (*manager.current_situation.player_list[id_player]).cards_in_hand.push_back(miss_card);

    EXPECT_TRUE(manager.is_miss(id_player));
}

TEST_F(TestGameSituation, simple_is_miss_02) {
    /// have not MISS card
    int id_player = 0;

    EXPECT_FALSE(manager.is_miss(id_player));
}

TEST_F(TestGameSituation, simple_bang_01) {
    /// simple bang - 1 HP
    int from_player = 0;
    int to_player = 1;

    int before_HP = manager.current_situation.player_list[to_player]->HP;
    manager.bang(from_player, to_player);
    int  after_HP = manager.current_situation.player_list[to_player]->HP;

    EXPECT_EQ(before_HP - 1, after_HP);
}

TEST_F(TestGameSituation, simple_bang_02) {
    /// simple bang - 1 HP and person dead and - 1 bandit
    int from_player = 0;
    int to_player = 1;

    (*manager.current_situation.player_list[to_player]).HP = 1;

    int before_HP = manager.current_situation.player_list[to_player]->HP;
    int before_bandits_count = manager.current_situation.count_bandits;
    manager.bang(from_player, to_player);

    int after_HP = manager.current_situation.player_list[to_player]->HP;
    int after_bandits_count = manager.current_situation.count_bandits;


    EXPECT_EQ(before_HP - 1, after_HP);
    EXPECT_TRUE(manager.current_situation.player_list[to_player]->is_dead);
    EXPECT_EQ(before_bandits_count - 1, after_bandits_count);
}

TEST_F(TestGameSituation, simple_bang_03) {
    /// simple bang with miss

    Card miss_card;
    miss_card.name_card = "[MISS]";

    int from_player = 0;
    int to_player = 1;
    (*manager.current_situation.player_list[to_player]).cards_in_hand.push_back(miss_card);

    size_t count_cards_before = (*manager.current_situation.player_list[to_player]).cards_in_hand.size();
    int before_HP = (*manager.current_situation.player_list[to_player]).HP;

    manager.bang(from_player, to_player);

    size_t count_cards_after = (*manager.current_situation.player_list[to_player]).cards_in_hand.size();
    int after_HP = (*manager.current_situation.player_list[to_player]).HP;

    EXPECT_EQ(before_HP, after_HP);
    EXPECT_EQ(count_cards_before - 1, count_cards_after);
}

TEST_F(TestGameSituation, simple_gun_01) {
    Card gun_card;
    gun_card.name_card = "[GUN]";

    int id_player = 0;

    (*manager.current_situation.player_list[id_player]).cards_in_hand.push_back(gun_card);
    size_t before_cards_coutn = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();
    int before_range = (*manager.current_situation.player_list[id_player]).range;

    manager.gun(id_player);

    size_t after_cards_coutn = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();
    int after_range = (*manager.current_situation.player_list[id_player]).range;

    EXPECT_EQ(before_range + 1, after_range);
    EXPECT_EQ(before_cards_coutn - 1, after_cards_coutn);
}

TEST_F(TestGameSituation, end_game_01) {
    /// rinnegan win
    /// 0 - bandit
    /// 1 - bandit
    /// 2 - bandit
    /// 3 - helper
    /// 4 - sheriff
    /// 5 - rinnegan

    (*manager.current_situation.player_list[0]).HP = 0;
    (*manager.current_situation.player_list[0]).is_dead = true;
    (*manager.current_situation.player_list[1]).HP = 0;
    (*manager.current_situation.player_list[1]).is_dead = true;
    (*manager.current_situation.player_list[2]).HP = 0;
    (*manager.current_situation.player_list[2]).is_dead = true;
    manager.current_situation.count_bandits = 0;

    (*manager.current_situation.player_list[4]).HP = 1;

    int from_player = 5;
    int to_player = 4;

    manager.bang(from_player, to_player);

    EXPECT_TRUE((*manager.current_situation.player_list[4]).is_dead);
    EXPECT_TRUE(manager.current_situation.is_end);
    EXPECT_EQ(manager.current_situation.WINNER, "rinnegan");
}

TEST_F(TestGameSituation, end_game_02) {
    /// bandits win
    /// 0 - bandit
    /// 1 - bandit
    /// 2 - bandit
    /// 3 - helper
    /// 4 - sheriff
    /// 5 - rinnegan

    (*manager.current_situation.player_list[0]).HP = 0;
    (*manager.current_situation.player_list[0]).is_dead = true;
    (*manager.current_situation.player_list[1]).HP = 0;
    (*manager.current_situation.player_list[1]).is_dead = true;
    manager.current_situation.count_bandits = 1;

    (*manager.current_situation.player_list[4]).HP = 1;

    int from_player = 5;
    int to_player = 4;

    manager.bang(from_player, to_player);

    EXPECT_TRUE((*manager.current_situation.player_list[4]).is_dead);
    EXPECT_TRUE(manager.current_situation.is_end);
    EXPECT_EQ(manager.current_situation.WINNER, "bandit");
}

TEST_F(TestGameSituation, end_game_03) {
    /// sheriff win
    /// 0 - bandit
    /// 1 - bandit
    /// 2 - bandit
    /// 3 - helper
    /// 4 - sheriff
    /// 5 - rinnegan

    (*manager.current_situation.player_list[0]).HP = 0;
    (*manager.current_situation.player_list[0]).is_dead = true;
    (*manager.current_situation.player_list[1]).HP = 0;
    (*manager.current_situation.player_list[1]).is_dead = true;
    (*manager.current_situation.player_list[2]).HP = 0;
    (*manager.current_situation.player_list[2]).is_dead = true;
    manager.current_situation.count_bandits = 0;

    (*manager.current_situation.player_list[5]).HP = 1;

    int from_player = 4;
    int to_player = 5;

    manager.bang(from_player, to_player);

    EXPECT_TRUE((*manager.current_situation.player_list[5]).is_dead);
    EXPECT_TRUE(manager.current_situation.is_end);
    EXPECT_EQ(manager.current_situation.WINNER, "sheriff");
}

TEST_F(TestGameSituation, add_2_cards_01) {
    int id_player = 0;

    size_t before_cards_count = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();

    manager.add_2_cards_before_move(id_player);

    size_t  after_cards_count = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();

    EXPECT_EQ(before_cards_count + 2, after_cards_count);
}

TEST_F(TestGameSituation, cards_count_01) {
    /// count is OK
    int id_player = 0;
    size_t before_cards_count = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();
    manager.add_2_cards_before_move(id_player);
    size_t  after_cards_count = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();
    EXPECT_EQ(before_cards_count + 2, after_cards_count);

    size_t HP = static_cast<size_t>((*manager.current_situation.player_list[id_player]).HP);
    EXPECT_TRUE(HP >= after_cards_count);
}

TEST_F(TestGameSituation, cards_count_02) {
    /// count is FAIL
    int id_player = 0;
    size_t before_cards_count = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();
    manager.add_2_cards_before_move(id_player);
    size_t  after_cards_count = (*manager.current_situation.player_list[id_player]).cards_in_hand.size();
    EXPECT_EQ(before_cards_count + 2, after_cards_count);

    (*manager.current_situation.player_list[id_player]).HP = 1;
    size_t HP = static_cast<size_t>((*manager.current_situation.player_list[id_player]).HP);
    EXPECT_FALSE(HP >= after_cards_count);
}

/*
 * Осталось довесить индекс карт, с корорыми взаимодействуем, чтобы кажждый раз не искать их в колоде
 * то есть почти во все функции с картами нужно совать cards_id! очень важно, а то не заработает
 *
 * остались тесты работы парсера и клиента
 * возможно нужно написать операторы равенства для структур
 */

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


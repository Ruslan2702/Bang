//
// Created by Екатерина Жарова on 12.11.2018.
//

#include <../GameController.h>
#include <Player.h>
#include <gtest/gtest.h>

class TestGameState : public ::testing::Test {
public:
    TestCard() { /* init protected members here */ }
    ~TestCard() { /* free protected members here */ }
    void SetUp() { /* called before every test */ }
    void TearDown() { /* called after every test */ }
};


TEST_F(TestGameState, testGameDistance) {
    Game game;
    Player * a = new Player();
    Player * b = new Player();
    Player * c = new Player();
    Player * d = new Player();
    game.addPlayer(a);
    game.addPlayer(b);
    game.addPlayer(c);
    game.addPlayer(d);
    a->setLife(2);
    b->setLife(2);
    c->setLife(2);
    d->setLife(2);

    ASSERT_EQ(game.getPlayers().size(), 4);
    ASSERT_EQ(game.getDistance(a, 1), 1);
    ASSERT_EQ(game.getDistance(a, 2), 2);
    ASSERT_EQ(game.getDistance(a, 3), 1);

    b->setLife(0);

    ASSERT_EQ(game.getPlayers().size(), 4);
    ASSERT_EQ(game.getDistance(a, 2), 1);
    ASSERT_EQ(game.getDistance(a, 3), 1);

    b->setLife(2);

    ASSERT_EQ(game.getPlayers().size(), 4);
    ASSERT_EQ(game.getDistance(a, 1), 1);
    ASSERT_EQ(game.getDistance(a, 2), 2);
    ASSERT_EQ(game.getDistance(a, 3), 1);

    shared_ptr<PermanentCard> appalossa = shared_ptr<PermanentCard>(new PermanentCard("Appalossa", "", 1));
    appalossa->setDistanceTweak(-1);
    a->addCard(appalossa);
    a->layCard(0);

    ASSERT_EQ(game.getDistance(a, 1), 1);
    ASSERT_EQ(game.getDistance(a, 2), 1);
    ASSERT_EQ(game.getDistance(a, 3), 1);
    ASSERT_EQ(game.getDistance(b, 0), 1);
    ASSERT_EQ(game.getDistance(c, 0), 2);
    ASSERT_EQ(game.getDistance(d, 0), 1);

    shared_ptr<PermanentCard> mustang = shared_ptr<PermanentCard>(new PermanentCard("Mustang", "", 1));
    mustang->setDistanceTweak(1);
    b->addCard(mustang);
    b->layCard(0);

    ASSERT_EQ(game.getDistance(c, 1), 2);
    ASSERT_EQ(game.getDistance(a, 1), 1);
}

TEST_F(TestGameState, testGameUnlimitedBang) {
    Game game;
    Player * a = new Player();
    Player * b = new Player();
    game.addPlayer(a);
    game.addPlayer(b);
    a->setLife(3);
    b->setLife(3);

    shared_ptr<BangCard> bang = shared_ptr<BangCard>(new BangCard("Bang!", "", 2));
    bang->setTargetDistance(true);
    shared_ptr<GunCard> beer = shared_ptr<GunCard>(new GunCard("Beer", "", 1, 1));
    beer->setUnlimitedBang(true);
    a->addCard(bang);
    a->addCard(bang);
    a->addCard(volcanic);
    a->layCard(2);

    ASSERT_EQ(game.playCard(a, 0, 1) == Game::SUCCESS);
    ASSERT_EQ(game.playCard(a, 0, 1) == Game::SUCCESS);
}

TEST_F(TestGameState, testGameDiscardCard) {
    Game game;
    Player * a = new Player();
    Player * b = new Player();
    game.addPlayer(a);
    game.addPlayer(b);
    a->setLife(1);
    b->setLife(1);

    shared_ptr<GunCard> volcanic = shared_ptr<GunCard>(new GunCard("Volcanic", "", 1, 1));
    shared_ptr<DiscardCard> discard = shared_ptr<DiscardCard>(new DiscardCard("Cat Balou", "", 1));
    discard->setTargetAny(true);

    a->addCard(discard);
    b->addCard(volcanic);
    b->layCard(0);
    ASSERT_EQ(b->getPermanentCards().size(), 1);
    ASSERT_EQ(a->getCards().size(), 1);
    ASSERT_EQ(game.playCard(a, 0, 1, 0), Game::SUCCESS);
    ASSERT_EQ(b->getPermanentCards().size(), 0);
    ASSERT_EQ(a->getCards().size(), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


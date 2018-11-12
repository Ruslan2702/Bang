#include <../GameController.h>
#include <Player.h>
#include <gtest/gtest.h>

/* Тестируем игровой контроллер, поддержка кол-ва игроков, а так же исход игры */
//Поддерживает количество игроков определенной роли и отвечает за конец игры:
//1. Шериф — 1шт
//2. Ренигант — 1шт
//3. Бандос — 3шт
//4. Помошник шерифа — 1шт
class TestGameState : public ::testing::Test {
 public:
  TestGameState() { /* init protected members here */ }
  ~TestGameState() { /* free protected members here */ }
  void SetUp() { /* called before every test */ }
  void TearDown() { /* called after every test */ }

 protected:
  /* none yet */
};


TEST_F(TestGameState, GameDrawCard) {
  Game game;
  Player * a = new Player();
  Player * b = new Player();
  game.addPlayer(a);
  game.addPlayer(b);
  a->setLife(1);
  b->setLife(1);

  shared_ptr<GunCard> volcanic = shared_ptr<GunCard>(new GunCard("Volcanic", "", 1, 1));
  shared_ptr<DrawCard> draw = shared_ptr<DrawCard>(new DrawCard("Panic", "", 1, 1));
  draw->setTargetDistance(true);

  a->addCard(draw);
  b->addCard(volcanic);
  b->layCard(0);
  ASSERT_EQ(b->getPermanentCards().size(), 1);
  ASSERT_EQ(a->getCards().size(), 1);
  ASSERT_EQ(game.playCard(a, 0, 1, 0), Game::SUCCESS);
  ASSERT_EQ(b->getPermanentCards().size(), 0);
  ASSERT_EQ(a->getCards().size(), 1);
}


TEST_F(TestGameState, GameOver) {
  Game game;
  Player * a = new Player();
  Player * b = new Player();
  Player * c = new Player();
  Player * d = new Player();
  game.addPlayer(a);
  game.addPlayer(b);
  game.addPlayer(c);
  game.addPlayer(d);

  RoleCard * sheriff = new RoleCard(RoleCard::SHERIFF, "", 1);
  RoleCard * renegate = new RoleCard(RoleCard::RENEGATE, "", 1);
  RoleCard * outlaw = new RoleCard(RoleCard::OUTLAW, "", 2);
  CharacterCard * character = new CharacterCard("Paul Regret", "", 1);
  character->setLife(3);

  a->setRole(sheriff);
  b->setRole(renegate);
  c->setRole(outlaw);
  d->setRole(outlaw);
  a->setCharacter(character);
  b->setCharacter(character);
  c->setCharacter(character);
  d->setCharacter(character);
  a->setLife(a->getMaxLife());
  b->setLife(b->getMaxLife());
  c->setLife(c->getMaxLife());
  d->setLife(d->getMaxLife());

  ASSERT_EQ(game.getWinners().size(), 0);
  a->setLife(0);
  ASSERT_EQ(game.getWinners().size(), 1);
  ASSERT_EQ(game.getWinners()[0],  RoleCard::OUTLAW);
  c->setLife(0);
  d->setLife(0);
  ASSERT_EQ(game.getWinners().size(), 1);
  ASSERT_EQ(game.getWinners()[0], RoleCard::RENEGATE);

  delete sheriff;
  delete renegate;
  delete outlaw;
  delete character;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

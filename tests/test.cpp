#include <GameController.h>
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
  TestCard() { /* init protected members here */ }
  ~TestCard() { /* free protected members here */ }
  void SetUp() { /* called before every test */ }
  void TearDown() { /* called after every test */ }

 protected:
  /* none yet */
};

/* Шериф победил — мертвы все бандосы и ренигант. */
TEST_F(TestGameState, StateSherif) {
GameState current(1, 0, 0, 1);
send_state::State result = current.to_game();
GameState finish = GameState::from_game(result);
ASSERT_EQ(current, finish);
}

/* Ренигант победил - шериф мертв и мертвы бандиты */
TEST_F(TestGameState, StateRenigant) {
GameState current(0, 1, 0, 1);
send_state::State result = current.to_game();
GameState finish = GameState::from_game(result);
ASSERT_EQ(current, finish);
}

/* Бандиты победили — мертвы шериф и ренигант. */
TEST_F(TestGameState, StateBanditos) {
GameState current(0, 0, 1, 1);
send_state::State result = current.to_game();
GameState finish = GameState::from_game(result);
ASSERT_EQ(current, finish);
}

/* Никто не победил, игра продолжается */
TEST_F(TestGameState, StateContinue) {
GameState current(1, 1, 1, 1);
send_state::State result = current.to_game();
GameState finish = GameState::from_game(result);
ASSERT_EQ(current, finish);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

//
// Created by antony on 29.10.18.
//

#ifndef CPPPROJECT_GAMECONTROLLER_H
#define CPPPROJECT_GAMECONTROLLER_H

#include "../net/GameClient.h"
#include "../net/GameServer.h"

/// Контроллер игрового окна.
class GameController : public Controller {
 private:
  /// Другие играют, мы ожидаем...
  static const int STATE_WAIT = 0;

  /// Наш ход начался. Выбор действий
  static const int STATE_ON_TURN = 1;

  /// Играть карту.
  static const int STATE_PLAY_CARD = 2;

  /// Выбираем цель для выбранной карты.
  static const int STATE_PLAY_TARGET = 3;

  /// Выбор карты из колоды.
  static const int STATE_PLAY_TARGET_CARD = 4;

  /// Выбор карты для защиты
  static const int STATE_DISCARD_CARD = 5;

  /// Ответ на ожидающую карты.
  static const int STATE_PENDING = 6;

  /// Конец игры.
  static const int STATE_GAME_OVER = 7;

  Game & game_;
  GameClient & client_;
  function<bool(vector<string>)> listener_;
  int state_ = GameController::STATE_WAIT;
  int error_ = Game::SUCCESS;
  vector<string> winners_;

  shared_ptr<PlayableCard> last_card_;
  string last_card_player_;
  int last_card_target_;

  /// Объединяет игровые состояния с игрового сервера.
  void update();

  void updatePlayersInfo();

  void updatePermanentCards();

  void updateCards();

  /// Отрисовка игрового окна и карты с игроками.
  void renderBoard();

  /// Отправляет запрос на сервер и обновляет состояние.
  void playCard(int position, int target = -1, int target_card = -1);

  /// Инициализирует блокировку входного сигнала
  void initInputHandler();

  /// Обрабатывает входящее событие из потока
  bool onStreamEvent(vector<string> event);
 public:
  GameController(Game & game, GameClient & client);

  /// Выбирает карту в руке и других игроков
  void actionInit();
};


#endif //CPPPROJECT_GAMECONTROLLER_H
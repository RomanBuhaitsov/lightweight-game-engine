#pragma once

#include "../game_window/game_window.h"
#include <string>

#include "level.h"

class Level1 : public Level {
public:
  Level1(GameWindow *game_window, MessageBus *message_bus);
  ~Level1();
  virtual void init();
  virtual void reset();
  virtual void update();

protected:
  virtual void onNotify(const Message & message);
};

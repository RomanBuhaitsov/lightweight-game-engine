#pragma once

#include "../game_window/game_window.h"
#include <string>

class Level : public BusNode {
private:
  std::string name;
  GameWindow *game_window;
  Level *next_level = nullptr;

public:
  Level(std::string name, GameWindow *game_window, MessageBus *message_bus);
  ~Level();

  Level *next();
  GameWindow *getGameWindow();
  virtual void init(){};
  virtual void reset(){};
  virtual void update(){};

protected:
  virtual void onNotify(Message message){};
};

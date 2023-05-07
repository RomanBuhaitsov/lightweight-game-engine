#pragma once

#include "../IO/io_manager.h"
#include "../game_window/game_window.h"
#include "../message_bus/bus.h"
#include "../texture_manager/texture_manager.h"

class GameLoop {
private:
  int framerate;
  int max_frameskip;
  int skip_ticks;
  MessageBus *message_bus;
  IOManager *io;
  GameWindow *window;
  TextureManager *texture_manager;

  void update(){};

protected:
  bool game_running; // TODO: consider moving this field to a more global scope

public:
  GameLoop(MessageBus *message_bus, IOManager *io, GameWindow *window,
           TextureManager *texture_manager, int framerate, int max_frameskip);
  GameLoop(){};
  ~GameLoop(){};

  void run();
};

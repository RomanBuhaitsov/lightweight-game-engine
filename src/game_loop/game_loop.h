#pragma once

#include "../IO/io_manager.h"
#include "../game_window/game_window.h"
#include "../texture_manager/texture_manager.h"

class GameLoop
{
private:
  int framerate;
  int max_frameskip;
  int skip_ticks;
  IOManager *io;
  GameWindow *window;
  TextureManager *texture_manager;
  
  void handleEvents(){};
  void update(){};

protected:
  bool game_running; // TODO: consider moving this field to a more global scope

public:
  GameLoop(IOManager *io, GameWindow *window, TextureManager *texture_manager, int framerate, int max_frameskip);
  GameLoop(){};
  ~GameLoop(){};

  void run();
};

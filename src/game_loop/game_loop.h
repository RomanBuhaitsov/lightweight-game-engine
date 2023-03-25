#pragma once

#include "../IO/io_manager.h"
#include "../LGE/LGE_RenderWindow.h"
class GameLoop
{
private:
  int framerate;
  int max_frameskip;
  int skip_ticks;
  int execution_start_time;
  IOManager *io;
  LGE_RenderWindow *window;

  void handleEvents(){};
  void update(){};

protected:
  bool game_running; // TODO: consider moving this field to a more global scope

public:
  GameLoop(IOManager *io, LGE_RenderWindow *window, int framerate, int max_frameskip);
  GameLoop(){};
  ~GameLoop(){};

  void run();
};

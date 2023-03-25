#include <fmt/format.h>
#include <iostream>

#include "game_loop/game_loop.h"
#include "IO/io_manager.h"
#include "LGE/LGE_GameWindow.h"
#include "config.cpp"

int main(int argc, char **argv)
{
  MessageBus *message_bus = new MessageBus();
  IOManager *io = new IOManager(message_bus);
  LGE_RenderWindow *window = new LGE_GameWindow("LGE", 800, 600, false);
  GameLoop *loop = new GameLoop(io, window, FRAMERATE, MAX_FRAMESKIP);
  loop->run();

  delete loop;
  return 0;
}

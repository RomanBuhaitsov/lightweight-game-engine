#include <fmt/format.h>
#include <iostream>

#include "game_loop/game_loop.h"
#include "game_window/game_window.h"
#include "IO/io_manager.h"

#include "config.cpp"

int main(int argc, char **argv)
{
  MessageBus *message_bus = new MessageBus();
  IOManager *io = new IOManager(message_bus);
  GameWindow *window = new GameWindow("LGE", 1920, 1080, false, FRAMERATE);
  TextureManager *texture_manager = new TextureManager(window, "src/static/textures");
  GameLoop *loop = new GameLoop(io, window, texture_manager, FRAMERATE, MAX_FRAMESKIP);
  loop->run();

  delete loop;
  return 0;
}

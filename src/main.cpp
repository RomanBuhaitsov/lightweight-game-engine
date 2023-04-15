#include <fmt/format.h>
#include <iostream>

#include "game_loop/game_loop.h"
#include "game_window/game_window.h"
#include "texture_manager/texture_manager.h"
#include "IO/io_manager.h"

#include "log.h"
#include "config.cpp"

int main(int argc, char **argv)
{
  Config *config = new Config();
  MessageBus *message_bus = new MessageBus();
  IOManager *io = new IOManager(message_bus);
  GameWindow *window = new GameWindow("LGE",
                                      config->getWindowWidth(),
                                      config->getWindowHeight(),
                                      false,
                                      config->getFramerate(),
                                      6,
                                      3,
                                      message_bus);
  TextureManager *texture_manager = new TextureManager(window, "src/static/textures");
  GameLoop *loop = new GameLoop(io, window, texture_manager, config->getFramerate(), config->getMaxFrameSkip());
  loop->run();

  delete loop;
  return 0;
}

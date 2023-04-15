#include <fmt/format.h>
#include <iostream>

#include "game_loop/game_loop.h"
#include "game_window/game_window.h"
#include "texture_manager/texture_manager.h"
#include "audio_manager/audio_manager.h"
#include "IO/io_manager.h"

#include "log.h"
#include "config.cpp"

int main(int argc, char **argv)
{
  MessageBus *message_bus = new MessageBus();
  IOManager *io = new IOManager(message_bus);
  GameWindow *window = new GameWindow("LGE", 1920, 1080, false, FRAMERATE);
  TextureManager *texture_manager = new TextureManager(window, "src/static/textures");
  AudioManager *audio_manager = new AudioManager(message_bus, "src/static/audio");
  GameLoop *loop = new GameLoop(io, window, texture_manager,audio_manager, FRAMERATE, MAX_FRAMESKIP);
  loop->run();

  delete loop;
  return 0;
}

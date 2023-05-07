#include <fmt/format.h>
#include <iostream>

#include "component/component.h"
#include "entity/entity_contact.h"
#include "game_loop/game_loop.h"
#include "game_window/game_window.h"
#include "texture_manager/texture_manager.h"
#include "IO/io_manager.h"
#include "audio_manager/audio_manager.h"

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
  Component::GAME = window;
  EntityContactListener *contact_listener = new EntityContactListener(message_bus);
  window->getWorld()->SetContactListener(contact_listener);
  TextureManager *texture_manager = new TextureManager(window, "src/static/textures");
  AudioManager *audio_manager = new AudioManager(window, "src/static/sound");
  GameLoop *loop = new GameLoop(io, window, texture_manager, audio_manager, config->getFramerate(), config->getMaxFrameSkip());
  loop->run();

  delete config;
  delete message_bus;
  delete io;
  delete window;
  delete contact_listener;
  delete texture_manager;
  delete audio_manager;
  delete loop;
  return 0;
}

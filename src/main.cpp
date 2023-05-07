#include <fmt/format.h>
#include <iostream>

#include "IO/io_manager.h"
#include "component/component.h"
#include "entity/entity_contact.h"

#include "game_loop/game_loop.h"
#include "game_window/game_window.h"
#include "level/levels.h"
#include "level/manager.h"
#include "texture_manager/texture_manager.h"

#include "config.cpp"
#include "log.h"

int main(int argc, char **argv) {
  Config *config = new Config();
  MessageBus *message_bus = new MessageBus();
  IOManager *io = new IOManager(message_bus);
  GameWindow *window =
      new GameWindow("LGE", config->getWindowWidth(), config->getWindowHeight(),
                     false, config->getFramerate(), 6, 3, message_bus);
  Component::GAME = window;
  EntityContactListener *contact_listener =
      new EntityContactListener(message_bus);
  window->getWorld()->SetContactListener(contact_listener);
  TextureManager *texture_manager =
      new TextureManager(window, "src/static/textures");
  Level *first_level = new Level1(window, message_bus);
  LevelManager *levels = new LevelManager(first_level, message_bus);
  GameLoop *loop =
      new GameLoop(levels, message_bus, io, window, texture_manager,
                   config->getFramerate(), config->getMaxFrameSkip());
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

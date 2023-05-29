#include <fmt/format.h>
#include <iostream>

#include "component/component.h"
#include "entity/entity_contact.h"
#include "game_loop/game_loop.h"
#include "game_window/game_window.h"
#include "level/manager.h"
#include "level/level_builder.h"
#include "texture_manager/texture_manager.h"
#include "audio_manager/audio_manager.h"
#include "IO/io_manager.h"

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
  //TextureManager* texture_manager =
  //    new TextureManager(window, "src/static/textures");
  AudioManager* audio_manager = new AudioManager(message_bus);
  LevelBuilder *level_builder = new LevelBuilder(window, message_bus);

  Level *first_level = level_builder->createFromJson("C:/Users/rbuha/university/lge2/lightweight-game-engine/src/static/levels/level1.json");
  LevelManager *levels = new LevelManager(first_level, message_bus);
  GameLoop *loop =
      new GameLoop(levels, message_bus, io, window, /*texture_manager,*/ audio_manager,
                   config->getFramerate(), config->getMaxFrameSkip());
  loop->run();

  delete config;
  delete io;
  delete window;
  delete contact_listener;
  //delete texture_manager;
  delete audio_manager;
  delete loop;
  delete message_bus; //MessageBus must be deleted last
  return 0;
}

#include <any>
#include <iostream>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../message_bus/message.h"

#include "io_manager.h"

void IOManager::update() {
  SDL_Event event;
  // SDL_PollEvent works only with initialized the video subsystem (e.g. game
  // window displayed)
  while (SDL_PollEvent(&event)) {
    if (event.type != SDL_KEYDOWN)
      continue;

    try {
      MessageEvent key_event = this->key_event_map.at(event.key.keysym.sym);
      Message message = Message(key_event);
      this->send(message);
    } catch (const std::out_of_range &oor) {
      return;
    }
  }
}

void IOManager::onNotify(Message message) {}

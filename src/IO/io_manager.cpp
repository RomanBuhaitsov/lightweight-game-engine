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
    if (event.type == SDL_QUIT) {
      this->send(Message(MessageEvent::QUIT));
      return;
    }
  }
  int num_keys = 0;
  const Uint8* key_states = SDL_GetKeyboardState(&num_keys);
  for (int i = 0; i < num_keys; ++i) {
      if (!key_states[i]) {
          continue;
      }
      try {
          MessageEvent key_event = this->key_event_map.at(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i)));
          Message message = Message(key_event);
          this->send(message);
      }
      catch (const std::out_of_range& oor) {
      }
  }
}

void IOManager::onNotify(const Message & message) {}

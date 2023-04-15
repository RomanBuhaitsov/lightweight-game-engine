#include <iostream>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../message_bus/message.h"

#include "io_manager.h"

void IOManager::update()
{
  SDL_Event event;
  // SDL_PollEvent works only with initialized the video subsystem (e.g. game window displayed)
  while (SDL_PollEvent(&event))
  {
    if (event.type != SDL_KEYDOWN)
      continue;

    MessageEvent key_event = this->key_event_map.at(event.key.keysym.sym);
    std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>();
    Message message = Message(key_event, data);
    send(message);
  }
}

void IOManager::onNotify(Message message)
{
  std::cout << "[IOManager] "
            << "received event" << std::endl;
}

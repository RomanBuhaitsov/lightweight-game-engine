#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

#include "game_loop.h"
#include "../IO/io_manager.h"

GameLoop::GameLoop(int framerate, int max_frameskip)
{
  this->framerate = framerate;
  this->max_frameskip = max_frameskip;
  this->skip_ticks = 1000 / this->framerate;
  this->game_running = true;
}

void GameLoop::run()
{
  int loops;
  auto next_game_tick = SDL_GetTicks64();

  // example of how to use the message bus
  MessageBus *message_bus = new MessageBus();
  IOManager *io_manager = new IOManager(message_bus);
  DummyReceiverClass *dummy_receiver = new DummyReceiverClass(message_bus);

  while (this->game_running)
  {
    loops = 0;
    while (SDL_GetTicks64() > next_game_tick && loops < this->max_frameskip)
    {
      io_manager->update();
      message_bus->notify();
      this->handleEvents();
      this->update();
      next_game_tick += this->skip_ticks;
      loops++;
    }

    this->render();
  }
}

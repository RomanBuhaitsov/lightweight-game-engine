#include <chrono>
#include <iostream>
#include <set>

#include <SDL2/SDL.h>

#include "../IO/io_manager.h"
#include "../game_window/game_window.cpp"
#include "../texture_manager/texture_manager.h"

#include "game_loop.h"

GameLoop::GameLoop(LevelManager *levels, MessageBus *message_bus, IOManager *io,
                   GameWindow *window, /*TextureManager* texture_manager,*/
                   int framerate, int max_frameskip)
    : BusNode(message_bus) {
  this->levels = levels;
  this->message_bus = message_bus;
  this->io = io;
  this->window = window;
  this->framerate = framerate;
  this->max_frameskip = max_frameskip;
  this->skip_ticks = 1000 / this->framerate;
  this->game_running = true;
  //this->texture_manager = texture_manager;
}

void GameLoop::onNotify(const Message & message) {
  switch (message.getEvent()) {
  case MessageEvent::ESCAPE_PRESSED:
  case MessageEvent::QUIT:
    this->game_running = false;
    break;
  default:
    break;
  }
}

void GameLoop::run() {
  this->levels->start();
  int loops;
  auto next_game_tick = SDL_GetTicks64();
  while (this->game_running) {
    loops = 0;
    while (SDL_GetTicks64() > next_game_tick && loops < this->max_frameskip) {
      this->io->update();
      this->window->update();
      this->message_bus->notify();
      this->window->present();
      next_game_tick += this->skip_ticks;
      loops++;
    }
    /*window->getWorld()->DebugDraw(); // uncomment this to debug draw box2d shapes */
  }
}

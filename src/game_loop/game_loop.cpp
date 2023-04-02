#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

#include "game_loop.h"
#include "../IO/io_manager.h"
#include "../LGE/LGE_RenderWindow.h"

// dependency injection
GameLoop::GameLoop(IOManager *io, LGE_RenderWindow *window, int framerate, int max_frameskip)
{
  this->io = io;
  this->window = window;
  this->framerate = framerate;
  this->max_frameskip = max_frameskip;
  this->skip_ticks = 1000 / this->framerate;
  this->game_running = true;
  this->execution_start_time = SDL_GetTicks64();
}

void GameLoop::run()
{
  int loops;
  auto next_game_tick = SDL_GetTicks64();
  SDL_Texture *texture = this->window->loadTexture("src/LGE/textures/placeholder.png");
  this->window->renderTexture(texture);
  this->window->present();

  while (this->game_running)
  {
    loops = 0;
    while (SDL_GetTicks64() > next_game_tick && loops < this->max_frameskip)
    {
      this->io->update();
      this->handleEvents();
      this->update();
      next_game_tick += this->skip_ticks;
      loops++;
    }
    // rendering should happen here
  }
}

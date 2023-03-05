#include <chrono>
#include <iostream>

#include "game_loop.h"

GameLoop::GameLoop(int framerate, int max_frameskip)
{
  this->framerate = framerate;
  this->max_frameskip = max_frameskip;
  this->skip_ticks = 1000 / this->framerate;
  this->game_running = true;
}

unsigned long long GameLoop::getTickCount()
{
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

void GameLoop::run()
{
  int loops;
  auto next_game_tick = this->getTickCount();

  while (this->game_running)
  {
    loops = 0;
    while (this->getTickCount() > next_game_tick && loops < this->max_frameskip)
    {
      this->handleEvents();
      this->update();
      next_game_tick += this->skip_ticks;
      loops++;
    }
    this->render();
  }
}

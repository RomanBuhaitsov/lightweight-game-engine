#include <chrono>
#include <iostream>
#include <set>

#include <SDL2/SDL.h>

/* #include "../debug_draw/debug_draw.h" */
/* #include "../entity/entity.h" */
/* #include "../entity/entity_contact.h" */
/* #include "../entity/entity_type.h" */
#include "../IO/io_manager.h"
#include "../game_window/game_window.cpp"
/* #include "../physics/physics_component.h" */
/* #include "../renderer/renderer.h" */
/* #include "../sprite/sprite_component.h" */
/* #include "../sprite/sprite_physics.h" */
#include "../texture_manager/texture_manager.h"

#include "../log.h"

#include "game_loop.h"

GameLoop::GameLoop(IOManager *io, GameWindow *window,
                   TextureManager *texture_manager, int framerate,
                   int max_frameskip) {
  this->io = io;
  this->window = window;
  this->framerate = framerate;
  this->max_frameskip = max_frameskip;
  this->skip_ticks = 1000 / this->framerate;
  this->game_running = true;
  this->texture_manager = texture_manager;
}

void GameLoop::run() {
  this->window->init();
  int loops;
  auto next_game_tick = SDL_GetTicks64();
  while (this->game_running) {
    loops = 0;
    while (SDL_GetTicks64() > next_game_tick && loops < this->max_frameskip) {
      //this->io->update(); //fixme: uncomment this once IO manager is fully functional
      /* this->handleEvents(); */
      /* this->update(); */
      this->window->update();
      this->window->present();
      next_game_tick += this->skip_ticks;
      loops++;
    }
    // rendering should happen here
    // this->window->present();
    /* this->window->getWorld() */
    /*     ->DebugDraw(); // uncomment this to debug draw box2d shapes */
  }
}

#include <chrono>
#include <iostream>
#include <set>

#include <SDL2/SDL.h>

#include "../debug_draw/debug_draw.h"
#include "../entity/entity.h"
#include "../entity/entity_contact.h"
#include "../entity/entity_type.h"
#include "../IO/io_manager.h"
#include "../game_window/game_window.cpp"
#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"
#include "../renderer/renderer.h"
#include "../texture_manager/texture_manager.h"
#include "../log.h"

#include "game_loop.h"

// dependency injection
GameLoop::GameLoop(IOManager *io, GameWindow *window, TextureManager *texture_manager, int framerate, int max_frameskip)
{
  this->io = io;
  this->window = window;
  this->framerate = framerate;
  this->max_frameskip = max_frameskip;
  this->skip_ticks = 1000 / this->framerate;
  this->game_running = true;
}

void GameLoop::run()
{
  SDL_Texture *background = (*this->texture_manager)["background.png"];
  SDL_Rect bg_src, bg_dest;
  bg_src.x = bg_src.y = 0;
  bg_src.w = 1920;
  bg_src.h = 1080;
  bg_dest.x = bg_dest.y = 0;
  bg_dest.w = 1280;
  bg_dest.h = 720;
  Component::game = this->window;
  SDL_Event ev;
  Uint64 frameStart, frameTime;
  const float timeStep = 1.0f / (float)this->framerate;
  const int velocityIterations = 8, positionIterations = 3;
  Entity *ent = new Entity(EntityType::ET_PLAYER);
  SDLDebugDraw debugDraw(this->window->renderer);
  debugDraw.SetFlags(b2Draw::e_shapeBit);
  this->window->world->SetDebugDraw(&debugDraw);
  int tileIndex = 0;
  ent->addComponent(new PhysicsComponent(PhysicsComponent::CharacterBody(0, 0, 24, 24, 0.1f)));
  ent->addComponent(new SpriteComponent((*this->texture_manager)["crudewalk.png"], 24, 28, 24, 28, {6, 6}, 100, 4));
  ent->addComponent(new SpritePhysicsHandler(PlayerMovementHandler));
  std::set<Entity *> entities;
  for (int i = 0; i < 16; ++i)
  {
    Entity *newTile = new Entity(EntityType::ET_GENERIC);
    newTile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(i * 32 - 1, 448, 32, 32, 0.8f)));
    newTile->addComponent(new SpriteComponent((*this->texture_manager)["grasstile.png"], 32, 32, 64, 64, 0, 0));
    newTile->addComponent(new SpritePhysicsHandler());
    entities.insert(newTile);
  }
  entities.insert(ent);
  EntityContactListener contact(this->window);
  this->window->world->SetContactListener(&contact);
  int loops;
  auto next_game_tick = SDL_GetTicks64();
  std::list<SDL_Event> recentEvents;
  std::list<Entity *> removeEntities;
  do
  {
    Log << "hejo" << std::endl;
    while (SDL_PollEvent(&ev))
    {
      recentEvents.push_back(ev);
      switch (ev.type)
      {
      case SDL_QUIT:
        this->game_running = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
      {
        switch (ev.button.button)
        {
        case SDL_BUTTON_LEFT:
        {
          Log << "Tile Index: " << tileIndex << '\n';
          Entity *gent = makeEntityFromIndex(tileIndex, ev, *(this->texture_manager));
          entities.insert(gent);
          break;
        }
        case SDL_BUTTON_RIGHT:
          if (++tileIndex == 4)
          {
            tileIndex = 0;
          }
          Log << "Tile Index: " << tileIndex << '\n';
          break;
        }
        break;
      }
      }
    }
    frameStart = SDL_GetTicks64();
    this->window->clear();
    this->window->renderTexture(background, bg_src, bg_dest);
    this->window->world->Step(timeStep, velocityIterations, positionIterations);
    for (Entity *gent : removeEntities)
    {
      gent->destroy();
      entities.erase(gent);
      delete gent;
    }
    removeEntities.clear();
    for (Entity *gent : entities)
    {
      if (gent != nullptr)
      {
        gent->update(frameStart);
        gent->draw();
      }
    }
    recentEvents.clear();
    // world->DebugDraw();
    this->window->present();
    frameTime = SDL_GetTicks64() - frameStart;
    if (this->framerate > frameTime)
    {
      SDL_Delay(this->framerate - frameTime);
    }
  } while (this->game_running);
  for (Entity *gent : entities)
  {
    if (gent != nullptr)
    {
      delete gent;
    }
  }
  entities.clear();

  /* while (this->game_running) */
  /* { */
  /*   loops = 0; */
  /*   while (SDL_GetTicks64() > next_game_tick && loops < this->max_frameskip) */
  /*   { */
  /*     this->io->update(); */
  /*     this->handleEvents(); */
  /*     this->update(); */
  /*     next_game_tick += this->skip_ticks; */
  /*     loops++; */
  /*   } */
  /*   // rendering should happen here */
  /* } */
}

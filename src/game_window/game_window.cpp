#include <set>

#include "../component/component.h"
#include "../debug_draw/debug_draw.h"
#include "../entity/entity.h"
#include "../entity/entity_contact.h"
#include "../physics/physics_component.h"
#include "../position/position_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"
#include "../texture_manager/texture_manager.h"

#include "../errors.cpp"
#include "game_window.h"

GameWindow::GameWindow(const char *title, int width, int height, bool fullscreen, int fps) : WindowRenderer(title, width, height, fullscreen), frameDelay(fps), textMgr(this)
{
  b2Vec2 gravity(0.0f, 10.0f);
  world = std::make_unique<b2World>(gravity);
}

void GameWindow::removeEntity(Entity *ent)
{
  removeEntities.push_back(ent);
}

const std::list<SDL_Event> &GameWindow::getRecentEvents() const
{
  return recentEvents;
}

Entity *makeEntityFromIndex(int index, SDL_Event &ev, const TextureManager &textMgr)
{
  if (index == 0)
  {
    Entity *newTile = new Entity(EntityType::ET_GENERIC);
    newTile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32, 32, 32, 0.8f)));
    newTile->addComponent(new SpriteComponent(textMgr["grasstile.png"], 32, 32, 64, 64));
    newTile->addComponent(new SpritePhysicsHandler());
    return newTile;
  }
  else if (index == 1)
  {
    Entity *newSlopeTile = new Entity(EntityType::ET_GENERIC);
    // newSlopeTile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32 - 1, 32, 32, 0.8f)));
    newSlopeTile->addComponent(new PhysicsComponent(
        PhysicsComponent::RightTriangleTileBody(
            ev.button.x / 32 * 32 - 1,
            ev.button.y / 32 * 32,
            32, 32, 0.8f)));
    newSlopeTile->addComponent(new SpriteComponent(textMgr["grass_slope_b.png"], 32, 32, 64, 64, 0, -16));
    newSlopeTile->addComponent(new SpritePhysicsHandler());
    return newSlopeTile;
  }
  else if (index == 2)
  {
    Entity *dynamicBox = new Entity(EntityType::ET_GENERIC);
    dynamicBox->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(
        ev.button.x / 32 * 32 - 1,
        ev.button.y / 32 * 32,
        32, 32, 0.8f, 0.1f, true)));
    dynamicBox->addComponent(new SpriteComponent(textMgr["wooden_box.png"], 32, 32, 32, 32, 0, 0));
    dynamicBox->addComponent(new SpritePhysicsHandler());
    return dynamicBox;
  }
  else if (index == 3)
  {
    Entity *coinEntity = new Entity(EntityType::ET_COLLECTIBLE);
    coinEntity->addComponent(new PhysicsComponent(PhysicsComponent::CharacterBody(
                                                      ev.button.x / 32 * 32 - 1,
                                                      ev.button.y / 32 * 32,
                                                      32 / 2, 32 / 2, 0.1f),
                                                  [](Entity *other) -> bool
                                                  {
                                                    if (other->getType() == EntityType::ET_PLAYER)
                                                    {
                                                      return true;
                                                    }
                                                    return false;
                                                  }));
    coinEntity->addComponent(new SpriteComponent(textMgr["coin.png"], 32 / 2, 32 / 2, 32, 32, {4}, 100, 32 / 4, 0));
    coinEntity->addComponent(new SpritePhysicsHandler());
    return coinEntity;
  }
  return nullptr;
}

void GameWindow::gameLoop()
{
  SDL_Texture *background = textMgr["background.png"];
  SDL_Rect bg_src, bg_dest;
  bg_src.x = bg_src.y = 0;
  bg_src.w = 1920;
  bg_src.h = 1080;
  bg_dest.x = bg_dest.y = 0;
  bg_dest.w = 1280;
  bg_dest.h = 720;
  Component::game = this;
  bool gameLoop = true;
  SDL_Event ev;
  const Uint64 desiredFrameTime = 1000 / frameDelay;
  Uint64 frameStart, frameTime;
  const float timeStep = 1.0f / (float)frameDelay;
  const int32 velocityIterations = 8, positionIterations = 3;
  Entity *ent = new Entity(EntityType::ET_PLAYER);
  SDLDebugDraw debugDraw(renderer);
  debugDraw.SetFlags(b2Draw::e_shapeBit);
  world->SetDebugDraw(&debugDraw);
  int tileIndex = 0;
  ent->addComponent(new PhysicsComponent(PhysicsComponent::CharacterBody(0, 0, 24, 24, 0.1f)));
  ent->addComponent(new SpriteComponent(textMgr["crudewalk.png"], 24, 28, 24, 28, {6, 6}, 100, 4));
  ent->addComponent(new SpritePhysicsHandler(PlayerMovementHandler));
  std::set<Entity *> entities;
  for (int i = 0; i < 16; ++i)
  {
    Entity *newTile = new Entity(EntityType::ET_GENERIC);
    newTile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(i * 32 - 1, 448, 32, 32, 0.8f)));
    newTile->addComponent(new SpriteComponent(textMgr["grasstile.png"], 32, 32, 64, 64, 0, 0));
    newTile->addComponent(new SpritePhysicsHandler());
    entities.insert(newTile);
  }
  entities.insert(ent);
  EntityContactListener contact(this);
  world->SetContactListener(&contact);
  do
  {
    while (SDL_PollEvent(&ev))
    {
      recentEvents.push_back(ev);
      switch (ev.type)
      {
      case SDL_QUIT:
        gameLoop = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
      {
        switch (ev.button.button)
        {
        case SDL_BUTTON_LEFT:
        {
          Log << "Tile Index: " << tileIndex << '\n';
          Entity *gent = makeEntityFromIndex(tileIndex, ev, textMgr);
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
    clear();
    renderTexture(background, bg_src, bg_dest);
    world->Step(timeStep, velocityIterations, positionIterations);
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
    present();
    frameTime = SDL_GetTicks64() - frameStart;
    if (desiredFrameTime > frameTime)
    {
      SDL_Delay(desiredFrameTime - frameTime);
    }
  } while (gameLoop);
  for (Entity *gent : entities)
  {
    if (gent != nullptr)
    {
      delete gent;
    }
  }
  entities.clear();
}

b2World *GameWindow::getWorld()
{
  return world.get();
}

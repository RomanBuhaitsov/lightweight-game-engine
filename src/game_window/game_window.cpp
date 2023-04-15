#include <optional>
#include <set>
#include <string>

#include "../component/component.h"
#include "../debug_draw/debug_draw.h"
#include "../entity/entity.h"
#include "../entity/entity_contact.h"
#include "../entity/builder.cpp"
#include "../physics/physics_component.h"
#include "../position/position_component.h"
#include "../renderer/renderer.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"
#include "../texture_manager/texture_manager.h"

#include "../log.h"
#include "../config.cpp"
#include "game_window.h"

Entity *makeEntityFromIndex(int index, int pos_x, int pos_y, const std::optional<SDL_Event> &ev, const TextureManager &texture_manager)
{
  if (index == 0)
  {
    if (!ev.has_value())
    {
      return NULL;
    }
    Entity *newTile = new Entity(EntityType::ET_GENERIC);
    newTile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(ev.value().button.x / 32 * 32 - 1, ev.value().button.y / 32 * 32, 32, 32, 0.8f)));
    newTile->addComponent(new SpriteComponent(texture_manager["grasstile.png"], 32, 32, 64, 64));
    newTile->addComponent(new SpritePhysicsHandler());
    return newTile;
  }
  else if (index == 1)
  {
    if (!ev.has_value())
    {
      return NULL;
    }
    Entity *newSlopeTile = new Entity(EntityType::ET_GENERIC);
    // newSlopeTile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32 - 1, 32, 32, 0.8f)));
    newSlopeTile->addComponent(new PhysicsComponent(
        PhysicsComponent::RightTriangleTileBody(
            ev.value().button.x / 32 * 32 - 1,
            ev.value().button.y / 32 * 32,
            32, 32, 0.8f)));
    newSlopeTile->addComponent(new SpriteComponent(texture_manager["grass_slope_b.png"], 32, 32, 64, 64, 0, -16));
    newSlopeTile->addComponent(new SpritePhysicsHandler());
    return newSlopeTile;
  }
  else if (index == 2)
  {
    if (!ev.has_value())
    {
      return NULL;
    }
    Entity *dynamicBox = new Entity(EntityType::ET_GENERIC);
    dynamicBox->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(
        ev.value().button.x / 32 * 32 - 1,
        ev.value().button.y / 32 * 32,
        32, 32, 0.8f, 0.1f, true)));
    dynamicBox->addComponent(new SpriteComponent(texture_manager["wooden_box.png"], 32, 32, 32, 32, 0, 0));
    dynamicBox->addComponent(new SpritePhysicsHandler());
    return dynamicBox;
  }
  else if (index == 3)
  {
    if (!ev.has_value())
    {
      return NULL;
    }
    Entity *coinEntity = new Entity(EntityType::ET_COLLECTIBLE);
    coinEntity->addComponent(new PhysicsComponent(PhysicsComponent::CharacterBody(
                                                      ev.value().button.x / 32 * 32 - 1,
                                                      ev.value().button.y / 32 * 32,
                                                      32 / 2, 32 / 2, 0.1f),
                                                  [](Entity *other) -> bool
                                                  {
                                                    if (other->getType() == EntityType::ET_PLAYER)
                                                    {
                                                      return true;
                                                    }
                                                    return false;
                                                  }));
    coinEntity->addComponent(new SpriteComponent(texture_manager["coin.png"], 32 / 2, 32 / 2, 32, 32, {4}, 100, 32 / 4, 0));
    coinEntity->addComponent(new SpritePhysicsHandler());
    return coinEntity;
  }
  else if (index == 4)
  {
    Entity *player = new Entity(EntityType::ET_PLAYER);
    player->addComponent(new PhysicsComponent(PhysicsComponent::CharacterBody(0, 0, 24, 24, 0.1f)));
    player->addComponent(new SpriteComponent(texture_manager["crudewalk.png"], 24, 28, 24, 28, {6, 6}, 100, 4));
    player->addComponent(new SpritePhysicsHandler(PlayerMovementHandler));
    return player;
  }
  else if (index == 5)
  {
    Entity *tile = new Entity(EntityType::ET_GENERIC);
    tile->addComponent(new PhysicsComponent(PhysicsComponent::TileBody(pos_x, pos_y, 32, 32, 0.8f)));
    tile->addComponent(new SpriteComponent(texture_manager["grasstile.png"], 32, 32, 64, 64, 0, 0));
    tile->addComponent(new SpritePhysicsHandler());
    return tile;
  }
  return nullptr;
}

GameWindow::GameWindow(const char *title,
                       int width,
                       int height,
                       bool fullscreen,
                       int fps,
                       int velocity_iterations,
                       int position_iterations,
                       MessageBus *message_bus) : WindowRenderer(title, width, height, fullscreen),
                                                  BusNode(message_bus),
                                                  texture_manager(this)
{
  this->framerate = fps;
  this->fullscreen = fullscreen;
  this->title = title;
  this->width = width;
  this->height = height;
  this->velocity_iterations = velocity_iterations;
  this->position_iterations = position_iterations;

  this->bg_src.x = this->bg_src.y = 0;
  this->bg_src.w = this->width;
  this->bg_src.h = this->height;

  this->bg_dest.x = this->bg_dest.y = 0;
  this->bg_dest.w = this->width;
  this->bg_dest.h = this->height;

  b2Vec2 gravity(0.0f, 10.0f);
  this->world = std::make_unique<b2World>(gravity);

  this->message_bus = message_bus;
}

GameWindow::~GameWindow()
{
  for (Entity *gent : this->entities)
  {
    if (gent != nullptr)
    {
      delete gent;
    }
  }
  this->entities.clear();
}

void GameWindow::setWidth(int width)
{
  this->width = width;
}

int GameWindow::getWidth()
{
  return width;
}

void GameWindow::setHeight(int height)
{
  this->height = height;
}

int GameWindow::getHeight()
{
  return height;
}

void GameWindow::setBackgroundTexture(SDL_Texture *bg_texture)
{
  this->bg_texture = bg_texture;
}

SDL_Texture *GameWindow::getBackgroundTexture()
{
  return bg_texture;
}

void GameWindow::removeEntity(Entity *ent)
{
  this->entities_to_remove.push_back(ent);
}

const std::list<SDL_Event> &GameWindow::getRecentEvents() const
{
  return recent_events;
}

void GameWindow::update()
{
  this->clear();
  this->renderTexture(this->bg_texture, bg_src, bg_dest);
  world->Step(1.0f / (float)this->framerate, this->velocity_iterations, this->position_iterations);
  for (Entity *gent : this->entities_to_remove)
  {
    gent->destroy();
    this->entities.erase(gent);
    delete gent;
  }
  this->entities_to_remove.clear();

  for (Entity *gent : this->entities)
  {
    if (gent != nullptr)
    {
      gent->update(3);
      gent->draw();
    }
  }
  recent_events.clear();
  present();
}

void GameWindow::onNotify(Message message)
{
  switch (message.getEvent())
  {
  case MessageEvent::LMB_PRESSED:
  {
    Entity *gent = makeEntityFromIndex(2, -1, -1, std::nullopt, this->texture_manager);
    this->entities.insert(gent);
    break;
  }
  case MessageEvent::RMB_PRESSED:
  {
    // do something
    Log << "RMB pressed" << std::endl;
    break;
  }
  default:
  {
    break;
  }
  }
}

void GameWindow::init()
{
  SDL_Texture *background = this->texture_manager["background.png"];
  this->setBackgroundTexture(background);
  Component::game = this;
  bool gameLoop = true;
  SDL_Event ev;
  const Uint64 desiredFrameTime = 1000 / framerate;
  Uint64 frameStart, frameTime;
  const float timeStep = 1.0f / (float)framerate;
  const int32 velocityIterations = 8, positionIterations = 3;

  SDLDebugDraw debugDraw(renderer);
  debugDraw.SetFlags(b2Draw::e_shapeBit);
  world->SetDebugDraw(&debugDraw);
  int tileIndex = 0;
  this->entities.insert(makeEntityFromIndex(4, -1, -1, std::nullopt, this->texture_manager));

  for (int i = 0; i < 16; ++i)
  {
    int pos_x = i * 32 - 1;
    int pos_y = 448;
    this->entities.insert(makeEntityFromIndex(5, pos_x, pos_y, std::nullopt, this->texture_manager));
  }
  EntityContactListener contact(this);
  world->SetContactListener(&contact);
}

b2World *GameWindow::getWorld()
{
  return world.get();
}

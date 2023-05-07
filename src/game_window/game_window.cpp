#include <optional>
#include <set>
#include <string>

#include <SDL2/SDL.h>

#include "../component/component.h"
#include "../entity/builder.cpp"
#include "../entity/entity.h"
#include "../entity/entity_contact.h"
#include "../entity/factory.h"
#include "../physics/physics_component.h"
#include "../position/position_component.h"
#include "../renderer/renderer.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"
#include "../texture_manager/texture_manager.h"

#include "../config.cpp"
#include "../log.h"

#include "game_window.h"

GameWindow::GameWindow(const char *title, int width, int height,
                       bool fullscreen, int fps, int velocity_iterations,
                       int position_iterations, MessageBus *message_bus)
    : WindowRenderer(title, width, height, fullscreen), BusNode(message_bus),
      texture_manager(this),
      debugDraw(new SDLDebugDraw(renderer, PhysicsComponent::M2P)) {
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

GameWindow::~GameWindow() {
  for (Entity *gent : this->entities) {
    if (gent != nullptr) {
      delete gent;
    }
  }
  this->entities.clear();
}

void GameWindow::setWidth(int width) { this->width = width; }

int GameWindow::getWidth() { return width; }

void GameWindow::setHeight(int height) { this->height = height; }

int GameWindow::getHeight() { return height; }

void GameWindow::setBackgroundTexture(SDL_Texture *bg_texture) {
  this->bg_texture = bg_texture;
}

SDL_Texture *GameWindow::getBackgroundTexture() { return bg_texture; }

void GameWindow::addEntity(Entity *entity) { this->entities.insert(entity); }

void GameWindow::removeEntity(Entity *ent) {
  this->entities_to_remove.push_back(ent);
}

const std::list<SDL_Event> &GameWindow::getRecentEvents() const {
  return recent_events;
}

void GameWindow::update() {
  this->clear();
  this->renderTexture(this->bg_texture, bg_src, bg_dest);
  world->Step(1.0f / (float)this->framerate, this->velocity_iterations,
              this->position_iterations);
  for (Entity *gent : this->entities_to_remove) {
    gent->destroy();
    this->entities.erase(gent);
    delete gent;
  }
  this->entities_to_remove.clear();

  for (Entity *gent : this->entities) {
    if (gent != nullptr) {
      gent->update(SDL_GetTicks64());
      gent->draw();
    }
  }
  recent_events.clear();
  // present(); //TEMP FIX
}

void GameWindow::onNotify(Message message) {}

void GameWindow::init() {
  SDL_Texture *background = this->texture_manager["background.png"];
  this->setBackgroundTexture(background);
  SDL_Event ev;
  const Uint64 desiredFrameTime = 1000 / framerate;
  Uint64 frameStart, frameTime;
  const float timeStep = 1.0f / (float)framerate;
  const int32 velocityIterations = 8, positionIterations = 3;

  debugDraw->SetFlags(b2Draw::e_shapeBit);
  world->SetDebugDraw(debugDraw.get());
  int tileIndex = 0;
  this->entities.insert(EntityFactory::createPlayer(
      0, 0, this->texture_manager["crudewalk.png"], this->message_bus));

  for (int i = 0; i < 16; ++i) {
    int pos_x = i * 32 - 1;
    int pos_y = 448;
    this->entities.insert(EntityFactory::createTile(
        pos_x, pos_y, this->texture_manager["grasstile.png"],
        this->message_bus));
  }
}

b2World *GameWindow::getWorld() { return world.get(); }

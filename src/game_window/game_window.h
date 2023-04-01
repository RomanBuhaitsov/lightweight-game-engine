#pragma once
#include "../renderer/renderer.h"
#include "../texture_manager/texture_manager.h"
#include "box2d/box2d.h"
#include <memory>
#include <list>

class Entity;

class GameWindow : public WindowRenderer
{
private:
  int frameDelay;

public:
  // TODO: this were private before, moved for testing
  std::unique_ptr<b2World> world;
  std::list<Entity *> removeEntities;
  TextureManager textMgr;
  std::list<SDL_Event> recentEvents;

  GameWindow(const char *title, int width, int height, bool fullscreen, int fps);
  void gameLoop();
  b2World *getWorld();
  void removeEntity(Entity *ent);
  const std::list<SDL_Event> &getRecentEvents() const;
};

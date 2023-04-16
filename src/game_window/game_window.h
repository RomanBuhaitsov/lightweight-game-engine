#pragma once
#include <list>
#include <memory>
#include <set>
#include <string>

#include "box2d/box2d.h"

#include "../message_bus/node.h"
#include "../renderer/renderer.h"
#include "../texture_manager/texture_manager.h"
#include "../config.cpp"

class Entity;
class SDLDebugDraw;

class GameWindow : public WindowRenderer, public BusNode
{
private:
  std::string title;
  int framerate;
  bool fullscreen;
  int width;
  int height;
  int velocity_iterations;
  int position_iterations;

  SDL_Rect bg_src;
  SDL_Rect bg_dest;
  SDL_Texture *bg_texture;
  std::unique_ptr<SDLDebugDraw> debugDraw;

  MessageBus *message_bus;

protected:
  virtual void onNotify(Message message);

public:
  // TODO: these were private before, moved for testing
  std::unique_ptr<b2World> world;
  std::list<Entity *> entities_to_remove;
  TextureManager texture_manager;
  std::list<SDL_Event> recent_events;
  std::set<Entity *> entities;

  void setWidth(int width);
  int getWidth();
  void setHeight(int height);
  int getHeight();
  void setBackgroundTexture(SDL_Texture *bg_texture);
  SDL_Texture *getBackgroundTexture();

  GameWindow(const char *title, int width, int height, bool fullscreen, int fps, int velocity_iterations, int position_iterations, MessageBus *message_bus);
  ~GameWindow();
  void init(); // this function will need to be extended e.g. take parameters specifying size of the window, entities list
  b2World *getWorld();
  void removeEntity(Entity *ent);
  const std::list<SDL_Event> &getRecentEvents() const;
  virtual void update();
};

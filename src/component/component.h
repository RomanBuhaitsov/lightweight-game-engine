#pragma once
#include "component_type.h"
#include "../game_window/game_window.h"

class Entity;

class Component
{
  friend Entity;

protected:
  Entity *entity;
  ComponentType type;

public:
  static GameWindow *game; // fixme: messagebus?
  Component(ComponentType type) : entity(NULL), type(type){};
  virtual void init(){};
  virtual void update(const Uint64 gameTime){};
  virtual void draw(){};
  // virtual void destroy() {}
  virtual ~Component(){};
};

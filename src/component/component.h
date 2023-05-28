#pragma once

#include <SDL2/SDL.h>

#include "../message_bus/node.h"
#include "../game_window/game_window.h"

#include "component_type.h"
#include <iostream>
class Entity;

class Component : public BusNode
{
  friend Entity;

protected:
  Entity *entity;
  ComponentType type;
  virtual void onNotify(const Message & message);

public:
  static GameWindow *GAME;
  Component(ComponentType type, MessageBus *message_bus) : BusNode(message_bus), entity(NULL), type(type){};
  virtual void init(){};
  virtual void update(const Uint64 gameTime){};
  virtual void update();
  virtual void draw(){};
  // virtual void destroy() {}
  virtual ~Component() {};
};

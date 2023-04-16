#pragma once

#include "SDL2/SDL.h"

#include "../component/component.h"
#include "../component/component_type.h"

class PositionComponent : public Component
{
private:
  int x;
  int y;

public:
  PositionComponent(MessageBus *message_bus) : Component(ComponentType::CT_POSITION, message_bus), x(0), y(0){};
  int getX() { return x; };
  int getY() { return y; };
  void update(const Uint64 gameTime);
  void draw(){};
  void setPos(const int &x, const int &y);
};

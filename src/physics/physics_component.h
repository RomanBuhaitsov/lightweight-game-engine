#pragma once
#include <cmath>
#include <functional>

#include "box2d/box2d.h"
#include <SDL2/SDL.h>

#include "../component/component.h"
#include "../message_bus/node.h"

class PhysicsComponent : public Component {
private:
  b2Body *body;

public:
  std::function<void(Entity *, Entity*, MessageBus*)> touch;
  std::function<void(Entity *, Entity*, MessageBus*)> detach;
  std::function<bool(Entity*)> can_collide;
  PhysicsComponent(b2Body *body, 
                  std::function<void(Entity *, Entity *, MessageBus*)> touch, 
                  std::function<void(Entity *, Entity*, MessageBus*)> detach, 
                  std::function<bool(Entity*)> can_collide,
                   MessageBus *message_bus);
  PhysicsComponent(b2Body *body, MessageBus *message_bus);
  void draw() override{};
  void init() override;
  b2Body *getBody();
  virtual json to_json();
  ~PhysicsComponent();
  const static float RAD2DEG;
  const static float M2P;
  const static float P2M;

  static b2Body *CharacterBody(int x, int y, int width, int height,
                               float friction);
  static b2Body *TileBody(int x, int y, int width, int height, float friction,
                          float density = 1.0f, bool dynamic = false);
  static b2Body *RightTriangleTileBody(int x, int y, int a, int b,
                                       float friction);
  static b2Body *ComplexFixtureBody(int x, int y, float friction);

};

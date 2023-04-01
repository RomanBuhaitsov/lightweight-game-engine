#pragma once
#include <cmath>
#include <functional>

#include "box2d/box2d.h"

#include "../component/component.h"

class PhysicsComponent : public Component
{
private:
  b2Body *body;

public:
  std::function<bool(Entity *)> touch; // return true => remove the entity
  // LGE_PhysicsComponent(int x, int y, int width, int height, float friction, b2BodyType bodyType);
  PhysicsComponent(b2Body *body, std::function<bool(Entity *)> touch);
  PhysicsComponent(b2Body *body);
  void draw() override{};
  void init() override;
  b2Body *getBody();
  ~PhysicsComponent();
  const static float RAD2DEG;
  const static float M2P;
  const static float P2M;

  static b2Body *CharacterBody(int x, int y, int width, int height, float friction);
  static b2Body *TileBody(int x, int y, int width, int height, float friction, float density = 1.0f, bool dynamic = false);
  static b2Body *RightTriangleTileBody(int x, int y, int a, int b, float friction);
  static b2Body *TestFixtureBody(int x, int y, float friction);

  friend class LGE_ContactListener;
};

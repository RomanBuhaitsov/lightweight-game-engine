#pragma once

#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"

#include "entity.h"

class EntityBuilder {
private:
  Entity *entity;

public:
  EntityBuilder(EntityType entityType);
  ~EntityBuilder();
  Entity reset();
  Entity addPhysics(PhysicsComponent *physicsComponent);
  Entity addSprite(SpriteComponent *spriteComponent);
  Entity addSpritePhysics(SpritePhysicsHandler *spritePhysics);
};

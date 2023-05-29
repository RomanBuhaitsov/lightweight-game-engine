#pragma once

#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"

#include "entity.h"

class EntityBuilder {
private:
  Entity *entity;

public:
  EntityBuilder(EntityType entityType, std::string name);
  ~EntityBuilder();
  EntityBuilder *reset();
  EntityBuilder *addPhysics(PhysicsComponent *physicsComponent);
  EntityBuilder *addSprite(SpriteComponent *spriteComponent);
  EntityBuilder *addSpritePhysics(SpritePhysicsHandler *spritePhysics);
  Entity *getEntity();
};

#pragma once

#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"
#include "../audio/audio_component.h"

#include "entity.h"

class EntityBuilder {
private:
  Entity *entity;

public:
  EntityBuilder(EntityType entityType);
  ~EntityBuilder();
  EntityBuilder *reset();
  EntityBuilder *addPhysics(PhysicsComponent *physicsComponent);
  EntityBuilder *addSprite(SpriteComponent *spriteComponent);
  EntityBuilder *addSpritePhysics(SpritePhysicsHandler *spritePhysics);
  EntityBuilder *addAudio(AudioComponent *audioComponent);
  Entity *getEntity();
};

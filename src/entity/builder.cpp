#include <iostream>
#include <optional>

#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"

#include "builder.h"
#include "entity.h"

EntityBuilder::EntityBuilder(EntityType entityType) {
  entity = new Entity(entityType);
}

EntityBuilder::~EntityBuilder() { delete entity; }

EntityBuilder *EntityBuilder::reset() {
  EntityType type = this->entity->getType();
  delete this->entity;
  this->entity = new Entity(type);
  return this;
}

EntityBuilder *EntityBuilder::addPhysics(PhysicsComponent *physicsComponent) {
  this->entity->addComponent(physicsComponent);
  return this;
}

EntityBuilder *EntityBuilder::addSprite(SpriteComponent *spriteComponent) {
  this->entity->addComponent(spriteComponent);
  return this;
}

EntityBuilder *
EntityBuilder::addSpritePhysics(SpritePhysicsHandler *spritePhysics) {
  this->entity->addComponent(spritePhysics);
  return this;
}

EntityBuilder *EntityBuilder::addAudio(AudioComponent *audioComponent) {
  this->entity->addComponent(audioComponent);
  return this;
}

Entity *EntityBuilder::getEntity() { return this->entity; }

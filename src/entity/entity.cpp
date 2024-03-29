#include <SDL2/SDL.h>
#include <optional>

#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"
#include "../sprite/sprite_physics.h"

#include "entity.h"

void Entity::addComponent(Component *component) {
  if (components.find(component->type) != components.end()) {
    delete component;
    return; // fixme: overwrite?
  }
  component->entity = this;
  component->init();
  components.insert(
      std::pair<ComponentType, Component *>(component->type, component));
}

Component *Entity::getComponent(const ComponentType type) {
  auto component = components.find(type);
  return component == components.end() ? NULL : component->second;
}

void Entity::update(const Uint64 gameTime) {
  for (auto &c : components) {
    c.second->update(gameTime);
  }
}

void Entity::draw() {
  for (auto &c : components) {
    c.second->draw();
  }
}

void Entity::destroy() {
  for (auto &c : components) {
    delete c.second;
  }
  components.clear();
}

Entity::Entity(EntityType entityType, std::string name) : entityType(entityType), name(name) {}

const EntityType &Entity::getType() const { return entityType; }

const std::string &Entity::getName() const { return name; }

Entity::~Entity() { 
  destroy(); }

#pragma once
#include <map>

#include "../component/component_type.h"
#include "../component/component.h"

#include "entity_type.h"

class Entity{
private:
  EntityType entityType;
  std::map<ComponentType, Component *> components;

public:
  void addComponent(Component *component);
  Component *getComponent(const ComponentType type);
  void update(const Uint64 gameTime);
  void draw();
  void destroy();
  const EntityType &getType() const;
  Entity(EntityType entityType);
  ~Entity();
};

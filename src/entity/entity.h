#pragma once
#include <map>
#include <nlohmann/json.hpp>

#include "../component/component_type.h"
#include "../component/component.h"

#include "entity_type.h"

class Entity{
private:
  EntityType entityType;
  std::map<ComponentType, Component *> components;
  std::string name;

public:
  void addComponent(Component *component);
  Component *getComponent(const ComponentType type);
  void update(const Uint64 gameTime);
  void draw();
  void destroy();
  const EntityType &getType() const;
  const std::string &getName() const;
  std::string entityInfo();
  Entity(EntityType entityType, std::string name);
  json to_json();
  ~Entity();
};

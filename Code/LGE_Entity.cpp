#include "LGE_Entity.h"

void LGE_Entity::addComponent(LGE_Component* component) {
	if (components.find(component->type) != components.end()) {
		delete component;
		return; //fixme: overwrite?
	}
	component->entity = this;
	component->init();
	components.insert(std::pair<LGE_ComponentType, LGE_Component*>(component->type, component));
}

LGE_Component* LGE_Entity::getComponent(const LGE_ComponentType type) {
	auto component = components.find(type);
	return component == components.end() ? NULL : component->second;
}

void LGE_Entity::update(const Uint64 gameTime) {
	for (auto & c : components) {
		c.second->update(gameTime);
	}
}

void LGE_Entity::draw() {
	for (auto & c : components) {
		c.second->draw();
	}
}

void LGE_Entity::destroy() {
	for (auto & c : components) {
		delete c.second;
	}
	components.clear();
}

LGE_Entity::LGE_Entity(LGE_EntityType entityType) : entityType(entityType) {
	
}

const LGE_EntityType& LGE_Entity::getType() const {
	return entityType;
}

LGE_Entity::~LGE_Entity() {
	destroy();
}
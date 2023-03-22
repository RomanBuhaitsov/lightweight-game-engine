#pragma once
#include <map>
#include "LGE_ComponentType.h"
#include "LGE_Components.h"
#include "LGE_EntityType.h"

class LGE_Entity {
private:
	LGE_EntityType entityType;
	std::map<LGE_ComponentType, LGE_Component*> components;
public:
	void addComponent(LGE_Component* component);
	LGE_Component* getComponent(const LGE_ComponentType type);
	void update(const Uint64 gameTime);
	void draw();
	void destroy();
	const LGE_EntityType& getType() const;
	LGE_Entity(LGE_EntityType entityType);
	~LGE_Entity();
};
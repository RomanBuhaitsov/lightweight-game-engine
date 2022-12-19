#pragma once
#include <map>
#include "LGE_Components.h"

class LGE_Entity {
private:
	std::map<LGE_ComponentType, LGE_Component*> components;
public:
	void addComponent(LGE_Component* component);
	LGE_Component* getComponent(const LGE_ComponentType & type);
	void update(const Uint64 & gameTime);
	void draw();
	void destroy();
	LGE_Entity();
	~LGE_Entity();
};
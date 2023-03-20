#pragma once
#include "LGE_GameWindow.h"
#include "LGE_ComponentType.h"

class LGE_Entity;

class LGE_Component {
	friend LGE_Entity;
protected:
	LGE_Entity* entity;
	LGE_ComponentType type;
public:
	static LGE_GameWindow* game; //fixme: messagebus?
	LGE_Component(LGE_ComponentType type) : entity(NULL), type(type) {};
	virtual void init() {};
	virtual void update(const Uint64 gameTime) {};
	virtual void draw() {};
	virtual ~LGE_Component() {};
};
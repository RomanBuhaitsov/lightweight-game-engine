#pragma once
#include "LGE_PhysicsComponent.h"
#include "LGE_Entity.h"
#include "LGE_EntityType.h"

class LGE_ContactListener : public b2ContactListener {
private:
	LGE_GameWindow* m_game;
public:
	LGE_ContactListener(LGE_GameWindow* game);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
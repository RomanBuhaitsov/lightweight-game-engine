#include "LGE_EntityContact.h"
#include "LGE_InputOutput.h"
#include <functional>

LGE_ContactListener::LGE_ContactListener(LGE_GameWindow* game) : m_game(game) { }

void LGE_ContactListener::BeginContact(b2Contact* contact) {
	//LGE_Log << __FUNCTION__ << " has been called\n";
	LGE_Entity *entityA = (LGE_Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer,
		*entityB = (LGE_Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (entityA && entityB) {
		LGE_PhysicsComponent* a = (LGE_PhysicsComponent*)entityA->getComponent(LGE_ComponentType::CT_PHYSICS),
			* b = (LGE_PhysicsComponent*)entityB->getComponent(LGE_ComponentType::CT_PHYSICS);
		if (a->touch) {
			if (a->touch(entityB)) {
				m_game->removeEntity(entityA);
				return;
			}
		}
		if (b->touch) {
			if (b->touch(entityA)) {
				m_game->removeEntity(entityB);
			}
		}

		/*LGE_EntityType typeA = entityA->getType(),
			typeB = entityB->getType();
		if (typeA == LGE_EntityType::ET_PLAYER && typeB == LGE_EntityType::ET_COLLECTIBLE) {
			LGE_Log << "entity B is a collectible and should be destroyed\n";
			m_game->removeEntity(entityB);
		}
		else if (typeA == LGE_EntityType::ET_COLLECTIBLE && typeB == LGE_EntityType::ET_PLAYER) {
			LGE_Log << "entity A is a collectible and should be destroyed\n";
			m_game->removeEntity(entityA);
		}*/
		
	}	
}

void LGE_ContactListener::EndContact(b2Contact* contact) {

}
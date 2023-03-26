#include "LGE_SpritePhysicsHandler.h"
#include "LGE_Entity.h"
#include "LGE_InputOutput.h"

LGE_SpritePhysicsHandler::LGE_SpritePhysicsHandler(std::function<void(LGE_SpriteComponent*, LGE_PhysicsComponent*, const std::list<SDL_Event>&)> handler) : LGE_Component(LGE_ComponentType::CT_SPHANDLER), handler(handler), sprite(NULL), physics(NULL)
{
}

LGE_SpritePhysicsHandler::LGE_SpritePhysicsHandler() : LGE_SpritePhysicsHandler(LGE_GenericSpritePhysicsHandler)
{
}

void LGE_SpritePhysicsHandler::init()
{
	sprite = (LGE_SpriteComponent*)entity->getComponent(LGE_ComponentType::CT_SPRITE);
	physics = (LGE_PhysicsComponent*)entity->getComponent(LGE_ComponentType::CT_PHYSICS);
	if (sprite == NULL) {
		LGE_Log << __FUNCTION__ << ": couldn't get the sprite component\n";
	}
	if (physics == NULL) {
		LGE_Log << __FUNCTION__ << ": couldn't get the physics component\n";
	}
}

void LGE_SpritePhysicsHandler::update(const Uint64 gameTime)
{
	if (sprite == NULL || physics == NULL) {
		return;
	}
	handler(sprite, physics, game->getRecentEvents());
}


void LGE_GenericSpritePhysicsHandler(LGE_SpriteComponent* sprite, LGE_PhysicsComponent* physics, const std::list<SDL_Event>& recentEvents) {
	b2Body* body = physics->getBody();
	b2Vec2 position = body->GetPosition();
	sprite->setPosition(position.x * LGE_PhysicsComponent::M2P, position.y * LGE_PhysicsComponent::M2P);
	sprite->setAngle(body->GetAngle() * LGE_PhysicsComponent::RAD2DEG);
}
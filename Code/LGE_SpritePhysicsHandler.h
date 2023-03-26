#pragma once
#include "LGE_Components.h"
#include "LGE_SpriteComponent.h"
#include "LGE_PhysicsComponent.h"
#include <functional>

void LGE_GenericSpritePhysicsHandler(LGE_SpriteComponent* sprite, LGE_PhysicsComponent* physics, const std::list<SDL_Event>& recentEvents);
void LGE_PlayerMovementHandler(LGE_SpriteComponent* sprite, LGE_PhysicsComponent* physics, const std::list<SDL_Event>& recentEvents);

class LGE_SpritePhysicsHandler : public LGE_Component {
private:
	LGE_SpriteComponent* sprite;
	LGE_PhysicsComponent* physics;
	std::function<void(LGE_SpriteComponent*, LGE_PhysicsComponent*, const std::list<SDL_Event>&)> handler;
public:
	LGE_SpritePhysicsHandler(std::function<void(LGE_SpriteComponent*, LGE_PhysicsComponent*, const std::list<SDL_Event>&)> handler);
	LGE_SpritePhysicsHandler();
	void init() override;
	void update(const Uint64 gameTime) override;
};
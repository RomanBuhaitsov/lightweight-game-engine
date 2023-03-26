#include "LGE_SpritePhysicsHandler.h"
#include "LGE_InputOutput.h"

void LGE_PlayerMovementHandler(LGE_SpriteComponent* sprite, LGE_PhysicsComponent* physics, const std::list<SDL_Event> & recentEvents) {
	b2Body* body = physics->getBody();
	b2Vec2 position = body->GetPosition(), vel = body->GetLinearVelocity(), desiredVel(0.0f, 0.0f);
	Uint16 flip = sprite->getFlipped();
	sprite->setPosition(position.x * LGE_PhysicsComponent::M2P, position.y * LGE_PhysicsComponent::M2P);
	if (vel.LengthSquared() > 0.1) {
		sprite->setRow(1);
	}
	else {
		sprite->setRow(0);
	}
	for (auto& ev : recentEvents) {
		if (ev.type == SDL_KEYDOWN) {
			float scale = 20.0;
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				if (abs(vel.y) < 0.01) {
					desiredVel.y = -100.0 * scale;
				}
				break;
			case SDLK_a:
				if (vel.x > -5) {
					desiredVel.x = -5 * scale;
				}
				if (!(flip & SDL_FLIP_HORIZONTAL)) {
					sprite->flipHorizontally();
				}
				break;
			case SDLK_d:
				if (vel.x < 5) {
					desiredVel.x = 5 * scale;
				}
				if (flip & SDL_FLIP_HORIZONTAL) {
					sprite->flipHorizontally();
				}
				break;
			}
			if (desiredVel.x == 0.0) {
				desiredVel.x = vel.x * -10.0;
			}
			body->ApplyForce(desiredVel, body->GetWorldCenter(), true);
		}
	}
}
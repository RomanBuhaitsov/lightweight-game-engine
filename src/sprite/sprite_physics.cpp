
#include "sprite_physics.h"
#include "../entity/entity.h"
#include "../log.h"

SpritePhysicsHandler::SpritePhysicsHandler(std::function<void(SpriteComponent *, PhysicsComponent *, const std::list<SDL_Event> &)> handler) : Component(ComponentType::CT_SPHANDLER), handler(handler), sprite(NULL), physics(NULL)
{
}

SpritePhysicsHandler::SpritePhysicsHandler() : SpritePhysicsHandler(GenericSpritePhysicsHandler)
{
}

void SpritePhysicsHandler::init()
{
  sprite = (SpriteComponent *)entity->getComponent(ComponentType::CT_SPRITE);
  physics = (PhysicsComponent *)entity->getComponent(ComponentType::CT_PHYSICS);
  if (sprite == NULL)
  {
    Log << __FUNCTION__ << ": couldn't get the sprite component\n";
  }
  if (physics == NULL)
  {
    Log << __FUNCTION__ << ": couldn't get the physics component\n";
  }
}

void SpritePhysicsHandler::update(const Uint64 gameTime)
{
  if (sprite == NULL || physics == NULL)
  {
    return;
  }
  handler(sprite, physics, game->getRecentEvents());
}

void GenericSpritePhysicsHandler(SpriteComponent *sprite, PhysicsComponent *physics, const std::list<SDL_Event> &recentEvents)
{
  b2Body *body = physics->getBody();
  b2Vec2 position = body->GetPosition();
  sprite->setPosition(position.x * PhysicsComponent::M2P, position.y * PhysicsComponent::M2P);
  sprite->setAngle(body->GetAngle() * PhysicsComponent::RAD2DEG);
}

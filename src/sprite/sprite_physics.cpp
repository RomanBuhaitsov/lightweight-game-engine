
#include "sprite_physics.h"
#include "../entity/entity.h"
#include "../log.h"

SpritePhysicsHandler::SpritePhysicsHandler(
    MessageBus *message_bus,
    std::function<void(SpriteComponent *, PhysicsComponent *, Message *)>
        handler)
    : Component(ComponentType::CT_SPHANDLER, message_bus), handler(handler),
      sprite(NULL), physics(NULL) {}

SpritePhysicsHandler::SpritePhysicsHandler(MessageBus *message_bus)
    : SpritePhysicsHandler(message_bus, GenericSpritePhysicsHandler) {}

void SpritePhysicsHandler::init() {
  sprite = (SpriteComponent *)entity->getComponent(ComponentType::CT_SPRITE);
  physics = (PhysicsComponent *)entity->getComponent(ComponentType::CT_PHYSICS);
  if (sprite == NULL) {
    Log << __FUNCTION__ << ": couldn't get the sprite component\n";
  }
  if (physics == NULL) {
    Log << __FUNCTION__ << ": couldn't get the physics component\n";
  }
}

void SpritePhysicsHandler::update(const Uint64 gameTime) {
  if (sprite == NULL || physics == NULL) {
    return;
  }
  handler(sprite, physics, NULL);
}

void SpritePhysicsHandler::onNotify(Message message) {
  if (sprite == NULL || physics == NULL) {
    return;
  }
  handler(sprite, physics, &message);
}

void GenericSpritePhysicsHandler(SpriteComponent *sprite,
                                 PhysicsComponent *physics, Message *message) {
  b2Body *body = physics->getBody();
  b2Vec2 position = body->GetPosition();
  sprite->setPosition(position.x * PhysicsComponent::M2P,
                      position.y * PhysicsComponent::M2P);
  sprite->setAngle(body->GetAngle() * PhysicsComponent::RAD2DEG);
}

void PlayerMovementHandler(SpriteComponent *sprite, PhysicsComponent *physics,
                           Message *message) {
  b2Body *body = physics->getBody();
  b2Vec2 position = body->GetPosition(), vel = body->GetLinearVelocity(),
         desiredVel(0.0f, 0.0f);
  Uint16 flip = sprite->getFlipped();
  sprite->setPosition(position.x * PhysicsComponent::M2P,
                      position.y * PhysicsComponent::M2P);
  if (vel.LengthSquared() > 0.1) {
    sprite->setRow(1);
  } else {
    sprite->setRow(0);
  }
  float scale = 20.0;
  if (message == NULL) {
    return;
  }
  switch (message->getEvent()) {
  case MessageEvent::w_PRESSED:
    if (abs(vel.y) < 0.01) {
      desiredVel.y = -100.0 * scale;
    }
    break;

  case MessageEvent::a_PRESSED:
    if (vel.x > -5) {
      desiredVel.x = -5 * scale;
    }
    if (!(flip & SDL_FLIP_HORIZONTAL)) {
      sprite->flipHorizontally();
    }
    break;

  case MessageEvent::d_PRESSED:
    if (vel.x < 5) {
      desiredVel.x = 5 * scale;
    }
    if (flip & SDL_FLIP_HORIZONTAL) {
      sprite->flipHorizontally();
    }
    break;
  default:
    break;
  }
  if (desiredVel.x == 0.0) {
    desiredVel.x = vel.x * -10.0;
  }
  body->ApplyForce(desiredVel, body->GetWorldCenter(), true);
}

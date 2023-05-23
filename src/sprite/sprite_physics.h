#pragma once
#include <functional>
#include <list>

#include "../component/component.h"
#include "../message_bus/bus.h"
#include "../physics/physics_component.h"
#include "../sprite/sprite_component.h"

void GenericSpritePhysicsHandler(SpriteComponent *sprite,
                                 PhysicsComponent *physics, const Message *message);
void PlayerMovementHandler(SpriteComponent *sprite, PhysicsComponent *physics,
                           const Message *message);

class SpritePhysicsHandler : public Component {
private:
  SpriteComponent *sprite;
  PhysicsComponent *physics;
  std::function<void(SpriteComponent *, PhysicsComponent *, const Message*)> handler;

public:
  SpritePhysicsHandler(
      MessageBus *message_bus,
      std::function<void(SpriteComponent *, PhysicsComponent *, const Message*)>
          handler);
  SpritePhysicsHandler(MessageBus *message_bus);
  void init() override;
  void update(const Uint64 gameTime) override;

protected:
  virtual void onNotify(const Message & message);
};

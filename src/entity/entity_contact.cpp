#include <functional>

#include "../message_bus/message.h"
#include "../physics/physics_component.h"

#include "../log.h"

#include "entity_contact.h"

void EntityContactListener::BeginContact(b2Contact *contact)
{
  Entity *entityA = (Entity *)contact->GetFixtureA()->GetBody()->GetUserData().pointer,
         *entityB = (Entity *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
  if (entityA && entityB)
  {
    PhysicsComponent *a = (PhysicsComponent *)entityA->getComponent(ComponentType::CT_PHYSICS),
                     *b = (PhysicsComponent *)entityB->getComponent(ComponentType::CT_PHYSICS);

    Message message(MessageEvent::ENTITY_CONTACT);
    if (a->touch)
    {

      if (a->touch(entityB))
      {
        message.getData()["first_entity"] = entityA;
        message.getData()["second_entity"] = entityB;
        this->send(message);
        return;
      }
    }
    if (b->touch)
    {
      if (b->touch(entityA))
      {
        message.getData()["first_entity"] = entityB;
        message.getData()["second_entity"] = entityA;
        this->send(message);
      }
    }

    /*EntityType typeA = entityA->getType(),
      typeB = entityB->getType();
    if (typeA == EntityType::ET_PLAYER && typeB == EntityType::ET_COLLECTIBLE) {
      Log << "entity B is a collectible and should be destroyed\n";
      m_game->removeEntity(entityB);
    }
    else if (typeA == EntityType::ET_COLLECTIBLE && typeB == EntityType::ET_PLAYER) {
      Log << "entity A is a collectible and should be destroyed\n";
      m_game->removeEntity(entityA);
    }*/
  }
}

void EntityContactListener::EndContact(b2Contact *contact)
{
}

void EntityContactListener::update()
{
}

void EntityContactListener::onNotify(Message message)
{
}

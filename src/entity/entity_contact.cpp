#include <functional>

#include "../physics/physics_component.h"
#include "../log.h"

#include "entity_contact.h"

EntityContactListener::EntityContactListener(GameWindow *game) : m_game(game) {}

void EntityContactListener::BeginContact(b2Contact *contact)
{
  Entity *entityA = (Entity *)contact->GetFixtureA()->GetBody()->GetUserData().pointer,
         *entityB = (Entity *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
  if (entityA && entityB)
  {
    PhysicsComponent *a = (PhysicsComponent *)entityA->getComponent(ComponentType::CT_PHYSICS),
                     *b = (PhysicsComponent *)entityB->getComponent(ComponentType::CT_PHYSICS);
    if (a->touch)
    {
      if (a->touch(entityB))
      {
        m_game->removeEntity(entityA);
        return;
      }
    }
    if (b->touch)
    {
      if (b->touch(entityA))
      {
        m_game->removeEntity(entityB);
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

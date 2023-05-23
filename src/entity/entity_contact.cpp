#include <functional>

#include "../message_bus/message.h"
#include "../physics/physics_component.h"

#include "entity_contact.h"

void EntityContactListener::BeginContact(b2Contact *contact)
{
  Entity *entityA = (Entity *)contact->GetFixtureA()->GetBody()->GetUserData().pointer,
         *entityB = (Entity *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
  if (entityA && entityB)
  {
    PhysicsComponent *a = (PhysicsComponent *)entityA->getComponent(ComponentType::CT_PHYSICS),
                     *b = (PhysicsComponent *)entityB->getComponent(ComponentType::CT_PHYSICS);

    if (a->touch) {
        a->touch(entityA, entityB, messageBus);
    }
    if (b->touch) {
        b->touch(entityB, entityA, messageBus);
    }

  }
}

void EntityContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer,
        * entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (entityA && entityB)
    {
        PhysicsComponent* a = (PhysicsComponent*)entityA->getComponent(ComponentType::CT_PHYSICS),
            * b = (PhysicsComponent*)entityB->getComponent(ComponentType::CT_PHYSICS);
        if (a->can_collide) {
            if (!a->can_collide(entityB)) {
                contact->SetEnabled(false);
                return;
            }
        }
        if (b->can_collide) {
            if (!b->can_collide(entityA)) {
                contact->SetEnabled(false);
                return;
            }
        }
    }
}

void EntityContactListener::EndContact(b2Contact *contact)
{
}

void EntityContactListener::update()
{
}

void EntityContactListener::onNotify(const Message & message)
{
}

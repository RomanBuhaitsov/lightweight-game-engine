#pragma once

#include "../entity/entity.h"
#include "../entity/entity_type.h"
#include "../message_bus/node.h"

class EntityContactListener : public b2ContactListener, public BusNode
{
protected:
  virtual void onNotify(Message message);

public:
  EntityContactListener(MessageBus *message_bus) : BusNode(message_bus){};
  virtual void update();
  void BeginContact(b2Contact *contact);
  void EndContact(b2Contact *contact);
};

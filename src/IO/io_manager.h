#pragma once

#include <iostream>
#include <queue>

#include "../message_bus/node.h"
#include "consts.h"

class IOManager : public BusNode
{
private:
  const std::unordered_map<int, MessageEvent> key_event_map = KEY_EVENT_MAP;

public:
  IOManager(MessageBus *messageBus) : BusNode(messageBus){};
  virtual void update();

protected:
  virtual void onNotify(Message message);
};

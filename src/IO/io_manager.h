#pragma once

#include <iostream>
#include "../message_bus/node.h"

class IOManager : public BusNode
{
public:
  IOManager(MessageBus *messageBus) : BusNode(messageBus) {}
  virtual void update();

protected:
  virtual void onNotify(Message message);
};

class DummyReceiverClass : public BusNode
{
public:
  DummyReceiverClass(MessageBus *messageBus) : BusNode(messageBus) {}

  void update();

  void onNotify(Message message);
};

#pragma once

#include <functional>
#include <unordered_map>

#include "bus.h"
#include "message.h"

class BusNode
{
public:
  BusNode(MessageBus *messageBus);

  virtual void update(){};

  void operator()(const Message& message);

  ~BusNode();

protected:
  MessageBus *messageBus;

  void send(const Message & message);

  virtual void onNotify(const Message & message)
  {
    // TODO: implement some basic action if needed
  }
};

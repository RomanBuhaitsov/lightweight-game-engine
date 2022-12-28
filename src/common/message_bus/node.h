#pragma once
#include "bus.h"
#include "message.h"

#include <functional>

class BusNode {
public:
  BusNode(MessageBus *messageBus);

  virtual void update(){};

protected:
  MessageBus *messageBus;

  std::function<void(Message)> getNotifyFunc();

  void send(Message message);

  virtual void onNotify(Message message) {
    // TODO: implement some basic action if needed
  }
};

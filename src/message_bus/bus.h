#pragma once
#include "message.h"

#include <functional>
#include <queue>
#include <vector>

class BusNode;

class MessageBus {
private:
  std::vector<BusNode*> receivers;
  std::queue<Message> messages;

public:
  MessageBus(){};
  ~MessageBus(){};

  void addReceiver(BusNode *receiver);

  void sendMessage(const Message & message);

  void notify();

  void removeReceiver(BusNode* receiver);
};

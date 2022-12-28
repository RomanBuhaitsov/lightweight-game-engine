#pragma once
#include "message.h"

#include <functional>
#include <queue>
#include <vector>

class MessageBus {
private:
  std::vector<std::function<void(Message)>> receivers;
  std::queue<Message> messages;

public:
  MessageBus(){};
  ~MessageBus(){};

  void addReceiver(std::function<void(Message)> messageReceiver);

  void sendMessage(Message message);

  void notify();
};

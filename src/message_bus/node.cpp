#include "node.h"
#include "bus.h"
#include "message.h"

#include <functional>

BusNode::BusNode(MessageBus *messageBus)
{
  this->messageBus = messageBus;
  this->messageBus->addReceiver(this->getNotifyFunc());
}

void BusNode::send(Message message)
{
  messageBus->sendMessage(message);
}

std::function<void(Message)> BusNode::getNotifyFunc()
{
  auto messageListener = [=](Message message) -> void
  {
    this->onNotify(message);
  };
  return messageListener;
}

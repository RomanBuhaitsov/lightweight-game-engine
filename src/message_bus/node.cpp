#include "node.h"
#include "bus.h"
#include "message.h"
#include <functional>

BusNode::BusNode(MessageBus *messageBus)
{
  this->messageBus = messageBus;
  this->messageBus->addReceiver(this);
}

void BusNode::send(const Message & message)
{
  messageBus->sendMessage(message);
}

void BusNode::operator()(const Message& message) {
	this->onNotify(message);
}

BusNode::~BusNode() {
	messageBus->removeReceiver(this);
}
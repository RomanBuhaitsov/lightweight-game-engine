#include "bus.h"
#include "message.h"

#include <functional>
#include <queue>
#include <vector>
#include "node.h"

void MessageBus::addReceiver(BusNode* messageReceiver)
{
  receivers.push_back(messageReceiver);
}

void MessageBus::sendMessage(const Message & message) { messages.push(message); }

void MessageBus::notify()
{
  while (!messages.empty())
  {
    for (auto & iter = receivers.begin(); iter != receivers.end(); iter++)
    {
        (**iter)(messages.front());
    }
    messages.pop();
  }
}

void MessageBus::removeReceiver(BusNode* messageReceiver) {
    for (auto& it = receivers.begin(); it != receivers.end(); ++it) {
        if (*it == messageReceiver) {
            receivers.erase(it);
            break;
        }
    }
}

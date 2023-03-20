#include <unordered_map>

#include "io_manager.h"

void IOManager::update()
{
  std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>();
  data["hello"] = "world";
  Message message = Message(MessageEvent::HELLO, data);
  send(message);
}

void IOManager::onNotify(Message message)
{
  switch (message.getEvent())
  {
  case MessageEvent::HELLO:
    std::cout << "[IOManager] " << message.getData()["hello"] << std::endl;
    break;
  default:
    break;
  }
}

void DummyReceiverClass::update()
{
  std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>();
  data["hello"] = "world";
  Message message = Message(MessageEvent::HELLO, data);
  send(message);
}

void DummyReceiverClass::onNotify(Message message)
{
  switch (message.getEvent())
  {
  case MessageEvent::HELLO:
    std::cout << "[DummyReceiverClass] " << message.getData()["hello"] << std::endl;
    break;
  default:
    break;
  }
}

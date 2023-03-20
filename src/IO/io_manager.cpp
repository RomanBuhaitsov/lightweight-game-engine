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
  std::cout << "Data: " << message.getData()["hello"] << std::endl;
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
  std::cout << "Data: " << message.getData()["hello"] << std::endl;
}

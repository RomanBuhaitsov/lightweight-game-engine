#pragma once

#include <any>
#include <string>
#include <unordered_map>

#include "message_event.h"

class Message
{
private:
  MessageEvent messageEvent;
  std::unordered_map<std::string, std::any> messageData;

public:
  Message(const MessageEvent event);
  MessageEvent getEvent() const;
  std::unordered_map<std::string, std::any> & getData();
  std::any getData(std::string key) const;
  std::any operator[](const std::string& key) const;
  bool dataExists(std::string dataName) const;
};

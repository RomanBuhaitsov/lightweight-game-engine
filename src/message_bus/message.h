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
  MessageEvent getEvent();
  std::unordered_map<std::string, std::any> getData();
};

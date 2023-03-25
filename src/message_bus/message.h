#pragma once
#include <string>
#include <unordered_map>

#include "message_event.h"

class Message
{
private:
  MessageEvent messageEvent;
  std::unordered_map<std::string, std::string> messageData;

public:
  Message(const MessageEvent event, const std::unordered_map<std::string, std::string> data);
  MessageEvent getEvent();
  std::unordered_map<std::string, std::string> getData();
};

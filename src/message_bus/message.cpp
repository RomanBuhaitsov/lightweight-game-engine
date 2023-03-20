#include "message.h"

#include <string>
#include <unordered_map>

Message::Message(const MessageEvent event, const std::unordered_map<std::string, std::string> data)
{
  messageEvent = event;
  messageData = data;
}

MessageEvent Message::getEvent() { return messageEvent; }
std::unordered_map<std::string, std::string> Message::getData() { return messageData; }

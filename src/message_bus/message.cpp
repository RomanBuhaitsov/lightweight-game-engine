#include <any>
#include <string>
#include <unordered_map>

#include "message.h"

Message::Message(const MessageEvent event)
{
  messageEvent = event;
}

MessageEvent Message::getEvent() { return messageEvent; }
std::unordered_map<std::string, std::any> Message::getData() { return messageData; }

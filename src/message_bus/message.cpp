#include <any>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <iostream>

#include "message.h"

Message::Message(const MessageEvent event)
{
  messageEvent = event;
}

MessageEvent Message::getEvent() const { return messageEvent; }

std::unordered_map<std::string, std::any> & Message::getData() { return messageData; }

std::any Message::getData(std::string key) const
{
  return messageData.find(key)->second;
}

std::any Message::operator[](const std::string& key) const {
	return messageData.at(key);
}

bool Message::dataExists (std::string dataName) const {
  return messageData.count(dataName) > 0;
}

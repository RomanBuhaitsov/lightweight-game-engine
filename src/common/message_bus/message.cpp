#include "message.h"

#include <string>

Message::Message(const std::string event) { messageEvent = event; }

std::string Message::getEvent() { return messageEvent; }

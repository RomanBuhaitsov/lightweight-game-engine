#include "message.h"

#include <string>

Message::Message(const MessageEvent event) { messageEvent = event; }

MessageEvent Message::getEvent() { return messageEvent; }

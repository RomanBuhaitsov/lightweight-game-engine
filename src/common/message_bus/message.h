#pragma once
#include <string>

enum class MessageEvent {
  // TODO: add events
};

class Message {
private:
  MessageEvent messageEvent;

public:
  Message(const MessageEvent event);
  MessageEvent getEvent();
};

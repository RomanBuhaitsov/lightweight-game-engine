#pragma once
#include <string>

class Message {
private:
  std::string messageEvent;

public:
  Message(const std::string event);
  std::string getEvent();
};

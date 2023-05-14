
#include "manager.h"

LevelManager::LevelManager(Level *current_level, MessageBus *message_bus)
    : BusNode(message_bus), current_level(current_level) {}

LevelManager::~LevelManager() { delete this->current_level; }

void LevelManager::prev() {
  this->current_level = this->current_level->prev();
  if (this->current_level != nullptr) {
    this->send(Message(MessageEvent::QUIT));
  }
}

void LevelManager::next() {
  this->current_level = this->current_level->next();
  if (this->current_level != nullptr) {
    this->send(Message(MessageEvent::QUIT));
  }
}

void LevelManager::onNotify(Message message) {
  switch (message.getEvent()) {
  case MessageEvent::NEXT_LEVEL:
    this->next();
    break;
  default:
    break;
  }
}

void LevelManager::start() {
  if (this->current_level == nullptr)
    return;
  this->current_level->init();
}

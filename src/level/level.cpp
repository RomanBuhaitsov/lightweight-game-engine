#include "level.h"

Level::Level(std::string name, GameWindow *game_window, MessageBus *message_bus)
    : BusNode(message_bus), name(name), game_window(game_window) {}

Level::~Level() { 
  this->reset(); 
}

GameWindow *Level::getGameWindow() { return this->game_window; }

void Level::setNextLevel(Level *next_level) { this->next_level = next_level; }

void Level::setPreviousLevel(Level *previous_level) {
  this->previous_level = previous_level;
}

Level *Level::next() {
  this->reset();
  if (this->next_level != nullptr) {
    this->next_level->init();
  }
  return this->next_level;
}

Level *Level::prev() {
  this->reset();
  if (this->previous_level != nullptr) {
    this->previous_level->init();
  }
  return this->previous_level;
}

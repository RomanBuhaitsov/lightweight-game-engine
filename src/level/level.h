#pragma once

#include "../game_window/game_window.h"
#include "../entity/factory.h"
#include <string>
#include <nlohman/json.hpp>

class Level : public BusNode {
private:
  std::string name;
  GameWindow *game_window;
  Level *next_level = nullptr;
  Level *previous_level = nullptr;

public:
  Level(std::string name, GameWindow *game_window, MessageBus *message_bus);
  ~Level();

  Level *next();
  Level* prev();
  GameWindow *getGameWindow();
  void setNextLevel(Level *next_level);
  void setPreviousLevel(Level *next_level);
  void saveAsJson(){};
  void createFromJson(){};
  virtual void init(){};
  virtual void reset(){};
  virtual void update(){};
  
protected:
  virtual void onNotify(const Message & message){};
};

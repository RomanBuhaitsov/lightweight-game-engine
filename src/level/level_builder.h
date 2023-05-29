#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "level.h"

using json = nlohmann::json;

class LevelBuilder : public BusNode {
private:
  GameWindow *game_window;
  void setBackground(std::string texture);
  void addPlayer(std::string texture, int pos_x, int pos_y);
  void addAnimation(std::string texture, int pos_x, int pos_y, int speed, unsigned short cols, unsigned short rows, std::string track, int width, int lenght);
  void addTile(std::string texture, int pos_x, int pos_y);
  void addCoin(std::string texture, int pos_x, int pos_y);
  void addWithLineFunction(std::string texture, int interval, int start_x, int start_y, int end_x, 
    int end_y, std::function<void(std::string, int, int)> addObject);
public:
  LevelBuilder(GameWindow *game_window, MessageBus *message_bus);
  ~LevelBuilder();

  // void saveAsJson(); TODO
  Level* createFromJson(std::string path);
};

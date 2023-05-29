#pragma once
#include "../component/component_type.h"
#include <array>

class Entity;

class Camera {
private:
  Entity *follow;
  ComponentType type;
  unsigned int lastGameTime;
  int delay;
  int x;
  int y;
  int dest_x;
  int dest_y;
  int max_x;
  int max_y;
  int screen_width;
  int screen_height;
  int step_x;
  int step_y;
  std::array<int, 2> getEntityPosition();

public:
  Camera(int level_width, int level_height, int screen_width, int screen_height,
         int delay);
  Camera(int level_width, int level_height, int screen_width, int screen_height,
         int delay, int step_x, int step_y);
  void followEntity(Entity *follow, bool instant);
  void unfollowEntity();
  void setDestination(int dest_x, int dest_y);
  void update(unsigned int gameTime);
  void setDelay(int delay);
  const int getX();
  const int getY();
  void setSteps(int x, int y);
};
#include "camera.h"

#include "../entity/entity.h"
#include "../log.h"
#include "../physics/physics_component.h"
#include "../position/position_component.h"

static inline int clamp(int min, int val, int max) {
  if (val > max) {
    return max;
  }
  if (val < min) {
    return min;
  }
  return val;
}

std::array<int, 2> Camera::getEntityPosition() {
  if (follow != NULL) {
    switch (type) {
    case ComponentType::CT_POSITION: {
      PositionComponent *pos = (PositionComponent *)follow->getComponent(type);
      return {pos->getX(), pos->getY()};
    }
    case ComponentType::CT_PHYSICS: {
      PhysicsComponent *physics =
          (PhysicsComponent *)follow->getComponent(type);
      b2Body *body = physics->getBody();
      return {(int)(body->GetPosition().x * PhysicsComponent::M2P),
              (int)(body->GetPosition().y * PhysicsComponent::M2P)};
    }
    }
  }
  return {dest_x, dest_y}; // fixme: is it better to return destination or throw
                           // an exception?
}

Camera::Camera(int level_width, int level_height, int screen_width,
               int screen_height, int delay, int step_x, int step_y)
    : max_x(level_width), max_y(level_height), delay(delay), dest_x(0),
      dest_y(0), follow(NULL), lastGameTime(0), x(0), y(0),
      type(ComponentType::CT_NONE), screen_width(screen_width),
      screen_height(screen_height), step_x(step_x), step_y(step_y) {}

Camera::Camera(int level_width, int level_height, int screen_width,
               int screen_height, int delay)
    : Camera(level_width, level_height, screen_width, screen_height, delay, 1,
             1){};

void Camera::followEntity(Entity *follow, bool instant) {
  PhysicsComponent *physics =
      (PhysicsComponent *)follow->getComponent(ComponentType::CT_PHYSICS);
  PositionComponent *pos =
      (PositionComponent *)follow->getComponent(ComponentType::CT_POSITION);
  if (physics == NULL && pos == NULL) {
    LogError << "Camera::followEntity requires an entity with a valid Physics "
                "or Position component\n";
    return;
  }
  this->type =
      physics != NULL ? ComponentType::CT_PHYSICS : ComponentType::CT_POSITION;
  this->follow = follow;
  if (instant) {
    auto real_position = getEntityPosition();
    this->x = clamp(0, real_position[0], max_x);
    this->y = clamp(0, real_position[1], max_y);
  }
}

void Camera::unfollowEntity() {
  this->follow = NULL;
  this->type = ComponentType::CT_NONE;
}

void Camera::setDestination(int dest_x, int dest_y) {
  this->dest_x = clamp(0, dest_x, max_x);
  this->dest_y = clamp(0, dest_y, max_y);
  this->unfollowEntity();
}

void Camera::update(Uint32 gameTime) {
  if (gameTime - lastGameTime < delay) {
    return;
  }
  lastGameTime = gameTime;
  int dest_x, dest_y;
  if (this->follow == NULL) {
    dest_x = this->dest_x;
    dest_y = this->dest_y;
  } else {
    auto entity_position = getEntityPosition();
    dest_x = clamp(0, entity_position[0], max_x);
    dest_y = clamp(0, entity_position[1], max_y);
  }
  if (abs(x - dest_x) < step_x) {
    x = dest_x;
  } else if (x > dest_x) {
    x -= step_x;
  } else if (x < dest_x) {
    x += step_x;
  }
  if (abs(y - dest_y) < step_y) {
    y = dest_y;
  } else if (y > dest_y) {
    y -= step_y;
  } else if (x < dest_x) {
    y += step_y;
  }
}

void Camera::setDelay(int delay) { this->delay = delay; }

const int Camera::getX() { return clamp(0, x - screen_width / 2, max_x); }

const int Camera::getY() { return clamp(0, y - screen_height / 2, max_y); }

void Camera::setSteps(int x, int y) {
  this->step_x = x;
  this->step_y = y;
}

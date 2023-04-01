add_library(Sprite "")

target_sources(Sprite
  PRIVATE
  sprite_component.cpp
  sprite_physics.cpp
  PUBLIC
  sprite_component.h
  sprite_physics.h
)

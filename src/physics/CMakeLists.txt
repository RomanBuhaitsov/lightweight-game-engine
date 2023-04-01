add_library(Physics "")

target_sources(Physics
  PRIVATE
  physics_component.cpp
  PUBLIC
  physics_component.h
)

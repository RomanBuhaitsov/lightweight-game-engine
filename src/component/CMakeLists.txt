add_library(Component "")

target_sources(Component
  PRIVATE
  component.cpp
  PUBLIC
  component.h
  component_type.h
)

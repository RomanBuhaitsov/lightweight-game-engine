add_library(Physics "")

find_package(box2d CONFIG REQUIRED)

target_sources(Physics
  PRIVATE
  physics_component.cpp
  PUBLIC
  physics_component.h
)

target_link_libraries(Physics PRIVATE box2d::box2d)

add_library(GameWindow "")

find_package(box2d CONFIG REQUIRED)

target_sources(
  PRIVATE
  game_window.cpp
  PUBLIC
  game_window.h
)

target_link_libraries(Renderer PRIVATE box2d::box2d)

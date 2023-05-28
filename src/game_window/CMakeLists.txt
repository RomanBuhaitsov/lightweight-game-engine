add_library(GameWindow "")

find_package(box2d CONFIG REQUIRED)

target_sources(GameWindow
  PRIVATE
  game_window.cpp
  PUBLIC
  game_window.h
)

target_link_libraries(GameWindow PRIVATE box2d::box2d)
target_link_libraries(GameWindow PUBLIC MessageBus)
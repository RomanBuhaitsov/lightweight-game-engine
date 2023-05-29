add_library(Level "")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_sources(Level
  PUBLIC
  level.h
  level_builder.h
  manager.h
  PRIVATE
  level.cpp
  level_builder.cpp
  manager.cpp
)

target_link_libraries(Level
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(Level 
  PRIVATE
  $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
  SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(Level 
  PRIVATE 
  nlohmann_json::nlohmann_json)
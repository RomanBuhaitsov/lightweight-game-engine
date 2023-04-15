add_library(AudioComponent "")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

target_sources(AudioComponent
  PRIVATE
  audio_component.cpp
  PUBLIC
  audio_component.h
)

target_link_libraries(AudioComponent
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

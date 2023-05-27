add_library(AudioManager "")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

target_sources(AudioManager
  PRIVATE
  audio_manager.cpp
  music_player.cpp
  sfx_player.cpp
  PUBLIC
  audio_manager.h
  music_player.h
  sfx_player.h
)

target_link_libraries(AudioManager
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(AudioManager PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)

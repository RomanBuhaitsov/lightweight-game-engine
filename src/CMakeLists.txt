cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

project(lightweight-game-engine CXX)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

add_subdirectory(component)
add_subdirectory(camera)
add_subdirectory(debug_draw)
add_subdirectory(entity)
add_subdirectory(game_loop)
add_subdirectory(game_window)
add_subdirectory(IO)
add_subdirectory(level)
add_subdirectory(message_bus)
add_subdirectory(physics)
add_subdirectory(renderer)
add_subdirectory(position)
add_subdirectory(sprite)
add_subdirectory(audio)
add_subdirectory(audio_manager)
add_subdirectory(texture_manager)

add_executable(lightweight-game-engine)
target_sources(lightweight-game-engine PRIVATE main.cpp)

target_include_directories(lightweight-game-engine PRIVATE .)

target_link_libraries(lightweight-game-engine PRIVATE Component)
target_link_libraries(lightweight-game-engine PRIVATE Camera)
target_link_libraries(lightweight-game-engine PRIVATE DebugDraw)
target_link_libraries(lightweight-game-engine PRIVATE Entity)
target_link_libraries(lightweight-game-engine PRIVATE GameLoop)
target_link_libraries(lightweight-game-engine PRIVATE GameWindow)
target_link_libraries(lightweight-game-engine PRIVATE IO)
target_link_libraries(lightweight-game-engine PRIVATE MessageBus)
target_link_libraries(lightweight-game-engine PRIVATE Physics)
target_link_libraries(lightweight-game-engine PRIVATE Position)
target_link_libraries(lightweight-game-engine PRIVATE Renderer)
target_link_libraries(lightweight-game-engine PRIVATE Sprite)
target_link_libraries(lightweight-game-engine PRIVATE TextureManager)
target_link_libraries(lightweight-game-engine PRIVATE Level)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(lightweight-game-engine PRIVATE fmt::fmt)

target_link_libraries(lightweight-game-engine
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(lightweight-game-engine PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

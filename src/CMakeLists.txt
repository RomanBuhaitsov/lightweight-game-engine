cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

project(lightweight-game-engine CXX)

add_subdirectory(game_loop)
add_subdirectory(message_bus)
add_subdirectory(IO)
add_subdirectory(LGE)

add_executable(lightweight-game-engine)
target_sources(lightweight-game-engine PRIVATE main.cpp)

target_include_directories(lightweight-game-engine PRIVATE .)

target_link_libraries(lightweight-game-engine PRIVATE GameLoop)
target_link_libraries(lightweight-game-engine PRIVATE MessageBus)
target_link_libraries(lightweight-game-engine PRIVATE IO)
target_link_libraries(lightweight-game-engine PRIVATE LGE)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(lightweight-game-engine PRIVATE fmt::fmt)

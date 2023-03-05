add_subdirectory(common)
add_subdirectory(game_loop)
add_subdirectory(LGE)

add_executable(lightweight-game-engine)
target_sources(lightweight-game-engine PRIVATE main.cpp)

target_include_directories(lightweight-game-engine PRIVATE "${PROJECT_SOURCE_DIR}")

target_link_libraries(lightweight-game-engine PRIVATE LGE)
target_link_libraries(lightweight-game-engine PRIVATE game_loop)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(lightweight-game-engine PRIVATE fmt::fmt)
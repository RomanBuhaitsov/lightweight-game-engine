add_library(IO "")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_sources(IO
  PRIVATE
  PUBLIC
  io_manager.cpp
  io_manager.h
)

target_link_libraries(IO PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(IO
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(IO PUBLIC MessageBus)

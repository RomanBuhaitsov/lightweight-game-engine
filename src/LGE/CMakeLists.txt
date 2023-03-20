add_library(LGE "")
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_sources(LGE
  PRIVATE
  LGE_GameWindow.cpp
  LGE_RenderWindow.cpp
  PUBLIC
  LGE_GameWindow.h
  LGE_RenderWindow.h
)

target_link_libraries(LGE PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(LGE
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

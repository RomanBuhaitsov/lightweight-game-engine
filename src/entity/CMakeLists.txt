add_library(Entity "")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_sources(Entity
  PRIVATE
  builder.cpp
  entity.cpp
  entity_contact.cpp
  factory.cpp
  PUBLIC
  builder.h
  entity.h
  entity_contact.h
  entity_type.h
  factory.h
)

target_link_libraries(Entity
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(Entity PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

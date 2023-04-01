add_library(Entity "")

target_sources(Entity
  PRIVATE
  entity.cpp
  entity_contact.cpp
  PUBLIC
  entity.h
  entity_contact.h
  entity_type.h
)

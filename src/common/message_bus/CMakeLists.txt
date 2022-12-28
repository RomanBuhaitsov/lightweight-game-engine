add_library(message_bus "")

target_sources(message_bus
  PRIVATE
    bus.h
    message.h
    node.h
    bus.cpp
    message.cpp
    node.cpp
)

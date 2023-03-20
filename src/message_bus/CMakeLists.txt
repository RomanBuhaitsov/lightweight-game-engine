add_library(MessageBus "")

target_sources(MessageBus
  PRIVATE
  bus.cpp
  message.cpp
  node.cpp
  PUBLIC
  bus.h
  message.h
  node.h
)

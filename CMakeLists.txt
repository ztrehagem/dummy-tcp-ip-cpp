cmake_minimum_required(VERSION 3.7)

include_directories(src)

add_subdirectory(src/common)
add_subdirectory(src/sender)
add_subdirectory(src/receiver)
add_subdirectory(src/layers)

add_executable(client
  src/client.cpp
)
target_link_libraries(client
  sender
  layers
  common
)

add_executable(server
  src/server.cpp
)
target_link_libraries(server
  receiver
  layers
  common
)

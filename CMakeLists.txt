cmake_minimum_required(VERSION 3.7)
add_subdirectory(src/types)

add_executable(client
  src/client.cpp
  src/sender.cpp
)
target_link_libraries(client types)

add_executable(server
  src/server.cpp
  src/receiver.cpp
)
target_link_libraries(server types)

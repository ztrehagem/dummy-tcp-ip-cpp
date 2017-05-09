cmake_minimum_required(VERSION 3.7)
add_executable(client
  src/client.cpp
  src/sender.cpp
)
add_executable(server
  src/server.cpp
  src/receiver.cpp
)

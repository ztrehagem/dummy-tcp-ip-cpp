cmake_minimum_required(VERSION 3.7)
add_library(types STATIC
  serial.cpp
  layer1.cpp
  layer2.cpp
  data.cpp
  dtcp.cpp
  dip.cpp
)

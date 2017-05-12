cmake_minimum_required(VERSION 3.7)

add_subdirectory(layer1)
add_subdirectory(layer2)
add_subdirectory(layer3)

add_library(layers STATIC
  layers.cpp
)
target_link_libraries(layers
  layer1
  layer2
  layer3
)

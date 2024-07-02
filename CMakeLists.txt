cmake_minimum_required(VERSION 3.12)
project(ESP-Sim)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add your source files here
set(SOURCES
  main.cpp
  HUB75.h
  HUB75.cpp
  driver.h
  driver.cpp
  display.h
  display.cpp
  imgBuffer.h
  imgBuffer.cpp
)

 
# Add your library dependencies here
set(LIBRARIES
  # Add library dependencies here
  sfml-graphics
  sfml-window
  sfml-system
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
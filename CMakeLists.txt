cmake_minimum_required(VERSION 3.12)
project(ESP-Sim)

set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add your source files here
set(SOURCES
  main.cpp
  driver/HUB75.cpp
  driver/driver.cpp
  driver/display.cpp
  # matrix/chip.cpp
  # matrix/matrix-display.cpp
  # Add more source files here
)

# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 2.6.x)
# FetchContent_MakeAvailable(SFML)

# Add your include directories here
set(INCLUDE_DIRS
  include
  # Add more include directories here
  ${CMAKE_SOURCE_DIR}/matrix
  ${CMAKE_SOURCE_DIR}/driver
)

# Add your library dependencies here
set(LIBRARIES
  # Add library dependencies here
  sfml-graphics
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# target_compile_features(main PRIVATE cxx_std_17)
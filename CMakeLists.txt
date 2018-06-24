cmake_minimum_required(VERSION 3.5.1)
project(sfml-game-development)

# Generate compilation database for use with YCM.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++11 throughout.
set(CMAKE_CXX_STANDARD 11)

# Find SFML.
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SFML 2 REQUIRED network audio graphics window system)

# Create main executable target.
add_executable(main main.cpp game.cpp)
target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

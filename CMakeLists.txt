
cmake_minimum_required(VERSION 3.10)

# Project name
project(GameProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include PkgConfig module
include(FindPkgConfig)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_image package using pkg-config
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
include_directories(${SDL2TTF_INCLUDE_DIRS})


# Add executable
add_executable(conway main.cpp Game.cpp GameUI.cpp Button.cpp Conway.cpp)

# Link SDL2 and SDL2_image libraries
target_link_libraries(conway ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

# Include directories
target_include_directories(conway PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


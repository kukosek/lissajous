cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Lissajous)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

execute_process(COMMAND ${CMAKE_COMMAND}
  -D "RDIR=${CMAKE_CURRENT_SOURCE_DIR}"
  -P "scansources.cmake"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include("sources.cmake")

include_directories(${CMAKE_SOURCE_DIR})

#find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)
#pkg_check_modules(SDL2 REQUIRED sdl2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -march=native")
add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} SDL2::Main)

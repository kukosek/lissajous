cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Lissajous)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)


find_package(PkgConfig REQUIRED)
#find_package(SDL2 REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -march=native")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(LIBRARY_DIRS FpsCounter;TableManager;TableManager/ControlCircle;TableManager/ControlCircle/Circle)

set(LIBRARIES)
foreach(X IN ITEMS ${LIBRARY_DIRS}) # for each library dir
	add_subdirectory(${X}) # add it as a subdir
	string(REPLACE "/" ";" PATHLIST ${X}) # create var PATHLIST (splitted library dir)
	list(GET PATHLIST -1 last_item) # save last item of PATHLIST into last_item
	list(APPEND LIBRARIES ${last_item}) # append it to libraries
	# it will work only if you have a cmakelists.txt inside with
	# the same library name as the folder
endforeach()
message(${LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} ${LIBRARY_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${SDL2_CFLAGS_OTHER})

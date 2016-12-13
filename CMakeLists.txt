cmake_minimum_required(VERSION 3.2)
project(2smard)

# find needed libraries
find_package(moveio REQUIRED)
include_directories(${MOVEIO_INCLUDE_DIRS})

# Flags for the compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

# Add one/multiple programs
add_executable(2smard
	src/Main.cpp
	src/Config.cpp
	src/SequenceItem.cpp
)
target_include_directories(2smard PUBLIC include/)
target_link_libraries(2smard ${MOVEIO_LIBRARY})

install(TARGETS 2smard
        RUNTIME DESTINATION bin)

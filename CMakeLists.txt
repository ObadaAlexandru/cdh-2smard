cmake_minimum_required(VERSION 3.2)
project(2smard)

# find needed libraries
find_package(moveio REQUIRED)
include_directories(${MOVEIO_INCLUDE_DIRS})

# Flags for the compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14 -Wall")

# Add one/multiple programs
add_executable(2smard
	src/Main.cpp
	src/ConfigParser.cpp
	src/SequenceParser.cpp
	src/SequenceItem.cpp
	src/Tokenizer.cpp
	src/CliParser.cpp
	src/SequenceRunner.cpp
	src/EPSCaller.cpp
)
target_include_directories(2smard PUBLIC include/)
target_link_libraries(2smard ${MOVEIO_LIBRARY}
	systemd
)
# target_link_libraries(testADCS
# 	systemd
# )

install(TARGETS 2smard
        RUNTIME DESTINATION bin)

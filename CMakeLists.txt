cmake_minimum_required(VERSION 3.2)
project(2smard)

# find needed libraries
find_package(moveio REQUIRED)
include_directories(${MOVEIO_INCLUDE_DIRS})

# Flags for the compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14 -Wall")


# Add one/multiple programs
add_executable(2smard_activator
	src/ActivatorMain.cpp
	src/ConfigParser.cpp
	src/SequenceParser.cpp
	src/SequenceItem.cpp
	src/Tokenizer.cpp
	src/CliParser.cpp
	src/SequenceRunner.cpp
	src/EPSCaller.cpp
	src/PinReader.cpp
	src/Utility.cpp
)

add_executable(2smard_checker
	src/CheckerMain.cpp
	src/ConfigParser.cpp
	src/SequenceParser.cpp
	src/SequenceItem.cpp
	src/Tokenizer.cpp
	src/CliParser.cpp
	src/PinReader.cpp
	src/Utility.cpp
)
#
target_include_directories(2smard_checker PUBLIC include/)
target_link_libraries(2smard_checker ${MOVEIO_LIBRARY})

target_include_directories(2smard_activator PUBLIC include/)
target_link_libraries(2smard_activator ${MOVEIO_LIBRARY}
	systemd
)

install(TARGETS 2smard_activator
        RUNTIME DESTINATION bin)

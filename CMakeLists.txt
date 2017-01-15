cmake_minimum_required(VERSION 3.2)
project(2smard)

# find needed libraries
find_package(moveio REQUIRED)
include_directories(${MOVEIO_INCLUDE_DIRS})

# Flags for the compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14 -Wall")


set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
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

# Test
enable_testing()

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        )

add_test(tests ${PROJECT_TEST_NAME})
# ------------

target_include_directories(2smard_checker PUBLIC include/)
target_link_libraries(2smard_checker ${MOVEIO_LIBRARY})

target_include_directories(2smard_activator PUBLIC include/)
target_link_libraries(2smard_activator ${MOVEIO_LIBRARY}
	systemd
)

install(TARGETS 2smard_checker
        RUNTIME DESTINATION bin)

install(TARGETS 2smard_activator
        RUNTIME DESTINATION bin)

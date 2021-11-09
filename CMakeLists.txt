cmake_minimum_required(VERSION 3.16)
project(try C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-g -Wall -Werror -Wextra -O3 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)



set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/include/testy)

set(SRC_DIR ${DIR}/src)

set(TESTS_DIR ${DIR}/test)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(/include/testy)

add_library(f_letter STATIC
        ${INC_DIR}/find_letters.h
        ${SRC_DIR}/find_letters.c)

add_library(multi_compute_matrix MODULE
        ${INC_DIR}/find_letters.h
        ${SRC_DIR}/find_letters.c)

add_executable(TEST
        test/main.cpp)

target_include_directories(TEST PUBLIC ${INC_DIR})

target_link_libraries(TEST ${GTEST_LIBRARIES} Threads::Threads pthread -ldl f_letter)

enable_testing()



add_executable(try
        ${SRC_DIR}/main.c)

target_link_libraries(try Threads::Threads pthread -ldl f_letter)

target_include_directories(try PUBLIC ${INC_DIR})

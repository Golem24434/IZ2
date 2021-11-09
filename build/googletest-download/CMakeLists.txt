cmake_minimum_required(VERSION 3.1)

project(googletest-download NONE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -fprofile-arcs -ftest-coverage-pthread")

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.8.1
  SOURCE_DIR        "/home/omar/try/build/googletest-src"
  BINARY_DIR        "/home/omar/try/build/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

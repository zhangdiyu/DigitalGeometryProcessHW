cmake_minimum_required(VERSION 3.0.0)
project(hw1 VERSION 0.1.0)

find_package(OpenCV REQUIRED)
include(CTest)
enable_testing()

add_executable(hw1 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

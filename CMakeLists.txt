cmake_minimum_required(VERSION 3.10)
project(FastTopo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(fasttopo ${SOURCES})

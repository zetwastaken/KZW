cmake_minimum_required(VERSION 3.0)
project(LAB1_RPQ)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES src/Solution.cpp)

add_library(libsolution ${SOURCES})
target_include_directories(libsolution PUBLIC include)

add_executable(lab1_rpq main.cpp)
target_link_libraries(lab1_rpq libsolution)

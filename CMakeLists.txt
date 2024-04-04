cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(AlanWeb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-Wall" "-g")

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)


add_executable(${PROJECT_NAME} ${SRC_FILES})

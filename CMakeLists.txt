cmake_minimum_required(VERSION 3.28)
project(balls LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(balls)
target_include_directories(
    balls PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(extern)

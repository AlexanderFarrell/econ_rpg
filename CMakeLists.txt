cmake_minimum_required(VERSION 3.27)
project(econ_rpg C)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Werror -Wall")

add_subdirectory(src/engine)
add_subdirectory(src/base)
add_subdirectory(src/client)
add_subdirectory(src/editor)
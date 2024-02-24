cmake_minimum_required(VERSION 3.27)
project(econ_editor)

add_executable(${PROJECT_NAME} editor.c)
target_include_directories(${PROJECT_NAME} PUBLIC ../base ../engine)
target_link_libraries(${PROJECT_NAME} PUBLIC game_engine econ_rpg_base)
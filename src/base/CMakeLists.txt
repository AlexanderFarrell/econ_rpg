cmake_minimum_required(VERSION 3.27)
project(econ_rpg_base)

add_library(econ_rpg_base base.h base.c)

target_include_directories(econ_rpg_base PUBLIC ../engine)
target_link_libraries(econ_rpg_base PUBLIC game_engine)
cmake_minimum_required(VERSION 3.0)
project(<name project> C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)
add_executable(<name project> sources/main.c sources/character.c sources/character.h sources/items.c sources/items.h sources/main.h sources/craft.c sources/craft.h sources/save.c sources/save.h sources/map.c sources/map.h sources/interface.c sources/interface.h sources/Chest.c sources/Chest.h sources/monster.c sources/monster.h)

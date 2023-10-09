cmake_minimum_required(VERSION 3.26)
project(Bridge_Bot)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Werror)

add_subdirectory(bot)
add_subdirectory(game_engine)


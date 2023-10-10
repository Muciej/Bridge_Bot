cmake_minimum_required(VERSION 3.26)
project(Bridge_Bot)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -pedantic)

include(FetchContent)
FetchContent_Declare(
  GTest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

add_subdirectory(bot)
add_subdirectory(game_engine)


cmake_minimum_required(VERSION 3.26)
project(Bridge_Bot)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BOT_DIR Bot)
set(GAME_ENGINE_DIR GameEngine)
set(HUMAN_PLAYER_DIR HumanPlayer)

set(BOT_EXEC_NAME Bot)
set(GAME_ENGINE_EXEC_NAME GameEngine)
set(HUMAN_PLAYER_EXEC_NAME HumanPlayer)

add_compile_options(-Wall -Werror -pedantic)

include(FetchContent)
FetchContent_Declare(
  GTest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

add_subdirectory(external)
add_subdirectory(common)
add_subdirectory(${BOT_DIR})
add_subdirectory(${GAME_ENGINE_DIR})
add_subdirectory(${HUMAN_PLAYER_DIR})
add_subdirectory(experiments)

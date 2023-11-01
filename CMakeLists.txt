cmake_minimum_required(VERSION 3.16)
project(BridgeSuite)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  GTest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

add_subdirectory(common)
add_subdirectory(external)
add_subdirectory(GameEngine)
add_subdirectory(HumanPlayer)
add_subdirectory(Bot)
add_subdirectory(experiments)

enable_testing()

set(EXEC_NAME ut_${GAME_ENGINE_EXEC_NAME})

set(SOURCES
    utPlayer.cpp
    utCardsUtils.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)

target_include_directories(${EXEC_NAME} 
    PRIVATE ${Bridge_Bot_SOURCE_DIR}/${GAME_ENGINE_DIR}/include
)

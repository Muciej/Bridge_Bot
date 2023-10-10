enable_testing()

set(EXEC_NAME ut_GameEngine)

set(SOURCES
    utPlayer.cpp
    utCardsUtils.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)

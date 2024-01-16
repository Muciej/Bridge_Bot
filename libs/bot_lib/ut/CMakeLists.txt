enable_testing()

set(EXEC_NAME ut_${BOT_LIB_NAME})

set(SOURCES
    testBot.cpp
    testMoveOptimizers.cpp
    testStateEvaluator.cpp
    testMoveGenerator.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME} PRIVATE
    compiler_flags
    GTest::gtest_main
    bot_lib
    connection
)
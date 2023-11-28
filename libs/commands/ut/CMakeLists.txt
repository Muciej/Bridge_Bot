enable_testing()

set(EXEC_NAME ut_${COMMAND_LIB_NAME})

set(SOURCES
    testQueueContainer.cpp
    testCommandsUtils.cpp
    testCommandCreator.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME} PRIVATE
    compiler_flags
    GTest::gtest_main
    commands
)
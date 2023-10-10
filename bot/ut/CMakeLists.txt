enable_testing()

set(EXEC_NAME ut_Bot)

set(SOURCES
    tempTest.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)

enable_testing()

set(EXEC_NAME ut_${COMMAND_LIB_NAME})

set(SOURCES
    testQueueContainer.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)

target_include_directories(${EXEC_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}/common
)

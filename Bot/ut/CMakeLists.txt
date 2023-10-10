enable_testing()

set(EXEC_NAME ut_${BOT_EXEC_NAME})

set(SOURCES
    tempTest.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)

target_include_directories(${EXEC_NAME} 
    PRIVATE ${Bridge_Bot_SOURCE_DIR}/${GAME_ENGINE_DIR}/include
)
enable_testing()

set(EXEC_NAME ut_${GAME_ENGINE_NAME})

set(SOURCES
    utCardsUtils.cpp
    utPlayer.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17)

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)
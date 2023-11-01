enable_testing()

set(EXEC_NAME ut_${UTILS_LIB_NAME})

set(SOURCES
    dummyTest.cpp
)

add_executable(${EXEC_NAME} ${SOURCES})

target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17)

target_link_libraries(${EXEC_NAME}
    PRIVATE
        GTest::gtest_main
)
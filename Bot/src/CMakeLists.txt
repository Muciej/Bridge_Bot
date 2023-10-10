set(SOURCES
    main.cpp
)

add_executable(${BOT_EXEC_NAME} ${SOURCES})

target_include_directories(${BOT_EXEC_NAME}
    PRIVATE ${Bridge_Bot_SOURCE_DIR}/${BOT_DIR}/inc
)

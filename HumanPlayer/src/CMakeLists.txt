set(SOURCES
    main.cpp
)

add_executable(${HUMAN_PLAYER_EXEC_NAME} ${SOURCES})

target_include_directories(${HUMAN_PLAYER_EXEC_NAME}
    PRIVATE ${Bridge_Bot_SOURCE_DIR}/${HUMAN_PLAYER_DIR}/inc
)

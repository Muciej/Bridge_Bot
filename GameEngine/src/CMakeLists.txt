set(SOURCES
    main.cpp
    Game.cpp
    Player.cpp
)

add_executable(${GAME_ENGINE_EXEC_NAME} ${SOURCES})

target_include_directories(${GAME_ENGINE_EXEC_NAME}
    PRIVATE ${Bridge_Bot_SOURCE_DIR}/${GAME_ENGINE_DIR}/inc
)

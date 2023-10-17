set(SOURCES
    main.cpp
    Game.cpp
    Player.cpp
    GameManager.cpp
)

add_executable(${GAME_ENGINE_EXEC_NAME} ${SOURCES})

target_include_directories(${GAME_ENGINE_EXEC_NAME}
    PRIVATE ${Bridge_Bot_SOURCE_DIR}/${GAME_ENGINE_DIR}/inc
    PRIVATE ${CMAKE_SOURCE_DIR}/common
)

target_link_libraries(${GAME_ENGINE_EXEC_NAME}
    sockpp    
)
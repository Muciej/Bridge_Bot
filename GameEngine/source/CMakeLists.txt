file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${GAME_ENGINE_NAME}/*.hpp")

set(SOURCES
    main.cpp
    Game.cpp
    GameManager.cpp
    Player.cpp
)

add_executable(${GAME_ENGINE_NAME} ${SOURCES})

target_include_directories(${GAME_ENGINE_NAME} PUBLIC ../include)
target_compile_features(${GAME_ENGINE_NAME} PRIVATE cxx_std_17)

target_link_libraries( ${GAME_ENGINE_NAME} PRIVATE
    connection
    commands
)

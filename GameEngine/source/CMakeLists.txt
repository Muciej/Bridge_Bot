file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${GAME_ENGINE_NAME}/*.hpp")

set(SOURCES
    main.cpp
    GameManager.cpp
)

add_executable(${GAME_ENGINE_NAME} ${SOURCES})

target_include_directories(${GAME_ENGINE_NAME} PRIVATE ../include)

target_link_libraries( ${GAME_ENGINE_NAME} PRIVATE
    compiler_flags
    utils
    connection
    commands
)

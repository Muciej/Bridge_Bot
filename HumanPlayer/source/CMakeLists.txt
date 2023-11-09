file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${HUMAN_PLAYER_NAME}/*.hpp")

set(SOURCES
    main.cpp
)

add_executable(${HUMAN_PLAYER_NAME} ${SOURCES})

target_include_directories(${HUMAN_PLAYER_NAME} PRIVATE ../include)
target_link_libraries(${HUMAN_PLAYER_NAME} PUBLIC
    compiler_flags    
    connection
    commands
)


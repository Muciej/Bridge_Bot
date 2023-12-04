file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${BOT_NAME}/*.hpp")

set(SOURCES
    main.cpp
)

add_executable(${BOT_NAME} ${SOURCES} ${HEADER_LIST})

target_include_directories(${BOT_NAME} PRIVATE ../include)
target_link_libraries(${BOT_NAME} PRIVATE
    compiler_flags
    commands
    bot
    connection
)

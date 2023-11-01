file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${HUMAN_PLAYER_NAME}/*.hpp")

set(SOURCES
    main.cpp
)

add_executable(${HUMAN_PLAYER_NAME} ${SOURCES})

target_include_directories(${HUMAN_PLAYER_NAME} PUBLIC ../include)
target_compile_features(${HUMAN_PLAYER_NAME} PRIVATE cxx_std_17)

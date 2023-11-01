file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${BOT_NAME}/*.hpp")

set(SOURCES
    main.cpp
)

add_executable(${BOT_NAME} ${SOURCES})

target_include_directories(${BOT_NAME} PUBLIC ../include)
target_compile_features(${BOT_NAME} PRIVATE cxx_std_17)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${COMMAND_LIB_NAME}/*.hpp")

set(SOURCES
    QueueContainer.cpp
    CommandsUtils.cpp
    CommandCreator.cpp
)

add_library(${COMMAND_LIB_NAME} ${SOURCES} ${HEADER_LIST})

target_include_directories(${COMMAND_LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${COMMAND_LIB_NAME}
    compiler_flags
    utils
)
